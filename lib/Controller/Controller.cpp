#include "Controller.h"

Controller::Controller(int buttonPin, unsigned long runtimeMinutes) {
  _buttonPin = buttonPin;
  _runtimeLimit = runtimeMinutes * 60 * 1000;
  _lastButtonState = HIGH;
  _isRunning = false;
  _lastDebounceTime = 0;
}

void Controller::begin() {
  pinMode(_buttonPin, INPUT_PULLUP);
}

void Controller::update(int logLevel) {
  bool currentState = digitalRead(_buttonPin);

  // Knop logica (State Change + Debounce)
  if (currentState == LOW && _lastButtonState == HIGH) {
    if (millis() - _lastDebounceTime > 50) {
      _isRunning = !_isRunning;
      _lastDebounceTime = millis();

      if (_isRunning) {
        _startTime = millis();
        if (logLevel >= 1) WebSerial.println("[TIMER] Gestart via knop!");
      } else {
        if (logLevel >= 1) WebSerial.println("[TIMER] Handmatig gestopt.");
      }
    }
  }
  _lastButtonState = currentState;

  // Auto-stop logica
  if (_isRunning) {
    if (millis() - _startTime >= _runtimeLimit) {
      _isRunning = false;
      if (logLevel >= 1) WebSerial.println("[TIMER] Tijd is om. Auto-stop.");
    }
  }
}

bool Controller::isRunning() {
  return _isRunning;
}
