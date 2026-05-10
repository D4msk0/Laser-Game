#include "StepperMotor.h"

StepperMotor::StepperMotor(int pin1, int pin2, int pin3, int pin4, int sweepRange, float speed, unsigned long minWait, unsigned long maxWait)
  : _stepper(AccelStepper::HALF4WIRE, pin1, pin3, pin2, pin4)
{
  _sweepRange = sweepRange;
  _speed = speed;
  _minWait = minWait;
  _maxWait = maxWait;
  _waitUntil = 0;
  _waiting = false;

  _stepper.setMaxSpeed(_speed);
  _stepper.setAcceleration(200.0);
}

void StepperMotor::begin()
{
  _stepper.moveTo(random(0, _sweepRange + 1));
}

void StepperMotor::update(int logLevel)
{
  if (_waiting)
  {
    if (millis() >= _waitUntil)
    {
      _waiting = false;
      int target = random(0, _sweepRange + 1);
      _stepper.moveTo(target);

      if (logLevel >= 2)
      {
        String msg = "[STEPPER] Moving to: " + String(target);
        Serial.println(msg);
      }
    }
    return;
  }

  _stepper.run();

  if (_stepper.distanceToGo() == 0)
  {
    _waiting = true;
    _waitUntil = millis() + random(_minWait, _maxWait + 1);

    if (logLevel >= 2)
    {
      String msg = "[STEPPER] Waiting at: " + String(_stepper.currentPosition());
      Serial.println(msg);
    }
  }
}