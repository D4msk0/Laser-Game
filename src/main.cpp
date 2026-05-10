#include <Arduino.h>
#include <WebSerial.h>

#include "config.h"
#include "secrets.h"

#include "NetworkManager.h"
#include "ServoMotor.h"
#include "StepperMotor.h"
#include "Controller.h"

AsyncWebServer server(80);
NetworkManager network(ssid, password, &server);
ServoMotor Servo1(SERVO_PIN, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, SERVO_MIN_WAIT, SERVO_MAX_WAIT);
StepperMotor Stepper1(STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4, STEPPER_SWEEP, STEPPER_SPEED, STEPPER_MIN_WAIT, STEPPER_MAX_WAIT);
Controller controller(BUTTON_PIN, RUNTIME_MINUTES);

int debugLevel = DEBUG_LEVEL;

void handleWebMsg(uint8_t *data, size_t len)
{
  String msg = "";
  for (size_t i = 0; i < len; i++)
    msg += (char)data[i];
  msg.trim();
  msg.toLowerCase();

  if (msg == "debug status")
  {
    String levels = "[DEBUG] Current level: " + String(debugLevel) + "\n"
                  "  0 = Silent\n"
                  "  1 = Browser monitoring (WebSerial only)\n"
                  "  2 = Full debug (WebSerial + Serial + hardware logs)";
    WebSerial.println(levels);
    return;
  }

  if (msg.startsWith("debug "))
  {
    int newLevel = msg.substring(6).toInt();
    if (newLevel >= 0 && newLevel <= 2)
    {
      debugLevel = newLevel;
      WebSerial.println("[DEBUG] Level set to: " + String(debugLevel));
    }
    else
    {
      WebSerial.println("[DEBUG] Invalid level. Use 0, 1 or 2.");
    }
    return;
  }

  controller.handleMessage(data, len, debugLevel);
}

void setup()
{
  if (debugLevel > 0)
    Serial.begin(115200);

  network.begin(debugLevel);
  network.setMsgCallback(handleWebMsg);

  randomSeed(analogRead(34));

  controller.begin();
  controller.setLogCallback([](const String &msg)
                            {
  if (debugLevel >= 1) WebSerial.println(msg); });

  Servo1.begin();
  Servo1.setLogCallback([](const String &msg)
                        {
  if (debugLevel >= 2) WebSerial.println(msg); });

  Stepper1.begin();
  Stepper1.setLogCallback([](const String &msg)
                          {
  if (debugLevel >= 2) WebSerial.println(msg); });
}

void loop()
{
  controller.update(debugLevel);

  if (controller.isRunning())
  {
    Servo1.update(debugLevel);
    Stepper1.update(debugLevel);
  }
}