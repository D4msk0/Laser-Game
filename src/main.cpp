#include <Arduino.h>

const int LED_PIN = 2; // Built-in LED on ESP32 DOIT DEVKIT V1

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
