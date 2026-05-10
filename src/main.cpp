#include <Arduino.h>
#include <WebSerial.h>

#include "NetworkManager.h"
#include "RandomServo.h"
#include "Controller.h"
#include "secrets.h"

#define DEBUG_LEVEL 2

AsyncWebServer server(80);
NetworkManager network(ssid, password, &server);
RandomServo Servo1(18, 12, 170, 200, 2000); // int pin, int minAngle, int maxAngle, int minWait, int maxWait
Controller controller(4, 15); // int pin, int time (minutes)

void handleWebMsg(uint8_t *data, size_t len) {
  controller.handleMessage(data, len, DEBUG_LEVEL);
}

void setup() {
  if (DEBUG_LEVEL > 0) Serial.begin(115200);

  network.begin(DEBUG_LEVEL);
  network.setMsgCallback(handleWebMsg);

  randomSeed(analogRead(34));

  controller.begin();
  controller.setLogCallback([](const String& msg) {
    if (DEBUG_LEVEL >= 1) Serial.println(msg);
    WebSerial.println(msg);
  });
  Servo1.begin();
}

void loop() {
  controller.update(DEBUG_LEVEL);

  if (controller.isRunning()) {
    Servo1.update(DEBUG_LEVEL);
  }
}
