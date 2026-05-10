#include "ServoMotor.h"

ServoMotor::ServoMotor(int pin, int minAngle, int maxAngle, int minWait, int maxWait) {
  _pin = pin;
  _minAngle = minAngle;
  _maxAngle = maxAngle;
  _minWait = minWait;
  _maxWait = maxWait;
  _prevTime = 0;
  _interval = 0;
  _logCallback = nullptr;
}

void ServoMotor::setLogCallback(void (*callback)(const String&))
{
  _logCallback = callback;
}

void ServoMotor::log(const String& msg)
{
  if (_logCallback) _logCallback(msg);
}

void ServoMotor::begin() {
  _servo.attach(_pin);
  _interval = random(_minWait, _maxWait);
}

void ServoMotor::update(int logLevel) {
  unsigned long currentTime = millis();
  
  if (currentTime - _prevTime >= _interval) {
    int randomAngle = random(_minAngle, _maxAngle + 1);
    _servo.write(randomAngle);
    
    _interval = random(_minWait, _maxWait);
    _prevTime = currentTime;

    // Only print when debug is true
    if (logLevel >= 2) {
      String msg = "[SERVO Pin " + String(_pin) + "] Angle: " + String(randomAngle);
      Serial.println(msg);
        log(msg);
    }
  }
}