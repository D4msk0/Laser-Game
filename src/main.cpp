#include <Arduino.h>
#include <WebSerial.h>

#include "config.h"
#include "secrets.h"

#include "NetworkManager.h"
#include "ServoMotor.h"
#include "Controller.h"

AsyncWebServer server(80);
NetworkManager network(ssid, password, &server);
ServoMotor Servo1(SERVO_PIN, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, SERVO_MIN_WAIT, SERVO_MAX_WAIT);
Controller controller(BUTTON_PIN, RUNTIME_MINUTES);

void handleWebMsg(uint8_t *data, size_t len)
{
  controller.handleMessage(data, len, DEBUG_LEVEL);
}

void setup()
{
  if (DEBUG_LEVEL > 0)
    Serial.begin(115200);

  network.begin(DEBUG_LEVEL);
  network.setMsgCallback(handleWebMsg);

  randomSeed(analogRead(34));

  controller.begin();
  controller.setLogCallback([](const String &msg)
                            {
#if (DEBUG_LEVEL >= 1) 
    Serial.println(msg);
#endif
    WebSerial.println(msg); });

  Servo1.begin();
}

void loop()
{
  controller.update(DEBUG_LEVEL);

  if (controller.isRunning())
  {
    Servo1.update(DEBUG_LEVEL);
  }
}
