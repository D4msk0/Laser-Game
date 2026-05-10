#include "Controller.h"

Controller::Controller(int buttonPin, unsigned long runtimeMinutes)
{
  _buttonPin = buttonPin;
  _runtimeLimit = (unsigned long)runtimeMinutes * 60UL * 1000UL;
  _lastButtonState = HIGH;
  _isRunning = false;
  _lastDebounceTime = 0;
}

void Controller::begin()
{
  pinMode(_buttonPin, INPUT_PULLUP);
}

void Controller::setLogCallback(void (*callback)(const String&))
{
  _logCallback = callback;
}

void Controller::log(const String& msg)
{
  if (_logCallback) _logCallback(msg);
}

bool Controller::start()
{
  if (_isRunning)
  {
    log("[SYSTEM] Already running. Command ignored.");
    return false;
  }
  _isRunning = true;
  _startTime = millis();
  log("[SYSTEM] Remote start received.");
  return true;
}

void Controller::stop()
{
  _isRunning = false;
  log("[SYSTEM] Remote stop received.");
}

void Controller::update(int logLevel)
{
  int currentState = digitalRead(_buttonPin);

  if (currentState == LOW && _lastButtonState == HIGH)
  {
    if (millis() - _lastDebounceTime > 50)
    {
      _isRunning = !_isRunning;
      _lastDebounceTime = millis();

      if (_isRunning)
      {
        _startTime = millis();
        String msg = "[TIMER] Started manually!";
        log(msg);
        if (logLevel >= 2) Serial.println(msg);
      }
      else
      {
        String msg = "[TIMER] Manually stopped.";
        log(msg);
        if (logLevel >= 2) Serial.println(msg);
      }
    }
  }
  _lastButtonState = currentState;

  if (_isRunning)
  {
    if (millis() - _startTime >= _runtimeLimit)
    {
      _isRunning = false;
      String msg = "[TIMER] Time is up. Auto-stop.";
      log(msg);
      if (logLevel >= 2) Serial.println(msg);
    }
  }
}

void Controller::handleMessage(uint8_t *data, size_t len, int logLevel)
{
  String msg = "";
  for (size_t i = 0; i < len; i++)
    msg += (char)data[i];
  msg.trim();
  msg.toLowerCase();

  if (logLevel >= 1)
  {
    Serial.print("[WEB-IN] Received: ");
    Serial.println(msg);
  }

  if (msg == "start")
  {
    if (this->start())
    {
      String out = "[WEB] System started";
      log(out);
      if (logLevel >= 2) Serial.println(out);
    }
  }
  else if (msg == "stop")
  {
    this->stop();
    String out = "[WEB] System stopped";
    log(out);
    if (logLevel >= 2) Serial.println(out);
  }
  else if (msg == "status")
  {
    if (_isRunning)
    {
      long timeLeft = getRemainingTime();
      String out = "[STATUS] Active. Remaining: " + String(timeLeft / 60) + "m " + String(timeLeft % 60) + "s";
      log(out);
      if (logLevel >= 2) Serial.println(out);
    }
    else
    {
      String out = "[STATUS] System is stand-by.";
      log(out);
      if (logLevel >= 2) Serial.println(out);
    }
  }
  else
  {
    String out = "[WEB] Unknown command: " + msg;
    log(out);
    if (logLevel >= 2) Serial.println(out);
  }
}

bool Controller::isRunning()
{
  return _isRunning;
}

long Controller::getRemainingTime()
{
  if (!_isRunning) return 0;
  unsigned long elapsed = millis() - _startTime;
  if (elapsed >= _runtimeLimit) return 0;
  return (_runtimeLimit - elapsed) / 1000;
}