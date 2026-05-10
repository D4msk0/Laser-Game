#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Arduino.h>
#include <ESP32Servo.h>

class ServoMotor {
  private:
    Servo _servo;
    int _pin;
    int _minAngle;
    int _maxAngle;
    int _minWait;
    int _maxWait;
    unsigned long _prevTime;
    unsigned long _interval;
    void (*_logCallback)(const String&) = nullptr;


  public:
    // Constructor
    ServoMotor(int pin, int minAngle, int maxAngle, int minWait, int maxWait);
    
    void begin();
    void update(int logLevel = 0);
    void setLogCallback(void (*callback)(const String&));
    void log(const String& msg);
};

#endif