#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <Arduino.h>
#include <AccelStepper.h>

class StepperMotor {
  private:
    AccelStepper _stepper;
    int _sweepRange;
    float _speed;
    unsigned long _minWait;
    unsigned long _maxWait;
    unsigned long _waitUntil;
    bool _waiting;
    void (*_logCallback)(const String&) = nullptr;

  public:
    StepperMotor(int pin1, int pin2, int pin3, int pin4, int sweepRange, float speed, unsigned long minWait, unsigned long maxWait);
    void begin();
    void update(int logLevel = 0);
    void setLogCallback(void (*callback)(const String&));
    void log(const String& msg);
};

#endif