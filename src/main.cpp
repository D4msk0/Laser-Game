#include <Arduino.h>
#include "NetworkManager.h"
#include "RandomServo.h"
#include "Controller.h"
#include "secrets.h"

#define DEBUG_LEVEL 2

AsyncWebServer server(80);
NetworkManager network(ssid, password, &server);
RandomServo Servo1(18, 12, 170, 200, 2000);
Controller controller(4, 15); // Pin 4, 15 minuten

void setup() {
  if (DEBUG_LEVEL > 0) Serial.begin(115200);

  network.begin(DEBUG_LEVEL);
  controller.begin();
  Servo1.begin();
  
  randomSeed(analogRead(34));
}

void loop() {
  controller.update(DEBUG_LEVEL);

  // Only let the servo's move if the controller is running
  if (controller.isRunning()) {
    Servo1.update(DEBUG_LEVEL);
  }
}
