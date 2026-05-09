#ifndef RANDOM_SERVO_H
#define RANDOM_SERVO_H

#include <Arduino.h>
#include <ESP32Servo.h>

class RandomServo {
  private:
    Servo _servo;
    int _pin;
    int _minAngle;
    int _maxAngle;
    int _minWait;
    int _maxWait;
    unsigned long _prevTime;
    unsigned long _interval;

  public:
    // Constructor
    RandomServo(int pin, int minAngle, int maxAngle, int minWait, int maxWait);
    
    void begin();
    void update(int logLevel = 0);
};

#endif