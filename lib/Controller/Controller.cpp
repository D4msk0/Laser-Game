#include "Controller.h"

Controller::Controller(int buttonPin, unsigned long runtimeMinutes)
{
  _buttonPin = buttonPin;
  _runtimeLimit = runtimeMinutes * 60 * 1000;
  _lastButtonState = HIGH;
  _isRunning = false;
  _lastDebounceTime = 0;
}

void Controller::begin()
{
  pinMode(_buttonPin, INPUT_PULLUP);
}

bool Controller::start()
{
  if (_isRunning)
  {
    WebSerial.println("[SYSTEM] Already running. Command ignored.");
    return false;
  }
  _isRunning = true;
  _startTime = millis();
  WebSerial.println("[SYSTEM] Remote start received.");
  return true;
}

void Controller::stop()
{
  _isRunning = false;
  WebSerial.println("[SYSTEM] Remote stop received.");
}

void Controller::update(int logLevel)
{
  bool currentState = digitalRead(_buttonPin);

  // Button logic (State Change + Debounce)
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
        WebSerial.println(msg);
        if (logLevel >= 1)
          Serial.println(msg);
      }
      else
      {
        String msg = "[TIMER] Manually stopped.";
        WebSerial.println(msg);
        if (logLevel >= 1)
          Serial.println(msg);
      }
    }
  }
  _lastButtonState = currentState;

  // Auto-stop logic
  if (_isRunning)
  {
    if (millis() - _startTime >= _runtimeLimit)
    {
      _isRunning = false;
      String msg = "[TIMER] Time is up. Auto-stop.";
      WebSerial.println(msg);
      if (logLevel >= 1)
        Serial.println(msg);
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

  if (msg == "start") {
    if (this->start()) {
      String out = "[WEB] System started";
      WebSerial.println(out);
      if (logLevel >= 1) Serial.println(out);
    }
  }
  else if (msg == "stop")
  {
    this->stop();
    String out = "[WEB] System stopped";
    WebSerial.println(out);
    if (logLevel >= 1)
      Serial.println(out);
  }
  else if (msg == "status")
  {
    if (_isRunning)
    {
      long timeLeft = getRemainingTime();

      WebSerial.printf("[STATUS] Active. Remaining: %ldm %lds\n", timeLeft / 60, timeLeft % 60);

      if (logLevel >= 1)
      {
        Serial.printf("[STATUS] Active. Remaining: %ldm %lds\n", timeLeft / 60, timeLeft % 60);
      }
    }
    else
    {
      String out = "[STATUS] System is stand-by.";
      WebSerial.println(out);
      if (logLevel >= 1)
        Serial.println(out);
    }
  }
  else
  {
    String out = "[WEB] Unknown command: " + msg;
    WebSerial.println(out);
    if (logLevel >= 1)
      Serial.println(out);
  }
}

bool Controller::isRunning()
{
  return _isRunning;
}

long Controller::getRemainingTime()
{
  if (!_isRunning)
    return 0;
  unsigned long elapsed = millis() - _startTime;
  if (elapsed >= _runtimeLimit)
    return 0;

  return (_runtimeLimit - elapsed) / 1000; // Return remaining time in seconds
}
