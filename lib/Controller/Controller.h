#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include <WebSerial.h>

class Controller {
  private:
    int _buttonPin;
    unsigned long _runtimeLimit;
    unsigned long _startTime;
    unsigned long _lastDebounceTime;
    int _lastButtonState;
    bool _isRunning;

  public:
    Controller(int buttonPin, unsigned long runtimeMinutes);
    void begin();
    void update(int logLevel = 0);
    bool start();
    void stop();
    void handleMessage(uint8_t *data, size_t len, int logLevel = 0);
    bool isRunning(); // Check to see if the controller is currently running
    long getRemainingTime(); // Get the remaining time in seconds
};

#endif
