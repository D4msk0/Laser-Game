#include <Arduino.h>
#include "NetworkManager.h"
#include "RandomServo.h"
#include "secrets.h"

// LOG LEVELS: 0 = Off, 1 = System, 2 = Detail
#define DEBUG_LEVEL 2 

AsyncWebServer server(80);
NetworkManager network(ssid, password, &server);
RandomServo Servo1(18, 12, 170, 200, 2000);

void setup() {
  if (DEBUG_LEVEL > 0) Serial.begin(115200);
  
  network.begin(DEBUG_LEVEL);
  randomSeed(analogRead(34));
  // Servo1.begin();
}

void loop() {
  network.update();
  Servo1.update(DEBUG_LEVEL);
}