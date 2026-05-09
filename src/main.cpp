#include <Arduino.h>

// LOG LEVELS: 0 = Off, 1 = System, 2 = Detail
#define DEBUG_LEVEL 0 
#include "RandomServo.h"

// Setup: Pin, MinAngle, MaxAngle, MinWait, MaxWait
RandomServo Servo1(18, 12, 170, 200, 2000);

void setup() {\
  if (DEBUG_LEVEL > 0) Serial.begin(9600);
  
  randomSeed(analogRead(34));
  
  // Servo1.begin();
}

void loop() {
  Servo1.update(DEBUG_LEVEL);
}