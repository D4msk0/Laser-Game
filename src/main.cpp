#include <Arduino.h>
#include "NetworkManager.h"
#include "RandomServo.h"
#include "secrets.h"

// LOG LEVELS: 0 = Off, 1 = System, 2 = Detail
#define DEBUG_LEVEL 2 

// Hardware settings
const int buttonPin = 4;
// Runtime settings (15 * 60 * 1000 = 15 minutes)
// 10 seconds for testing
const unsigned long runtimeLimit = 10 * 1000; 

// Objects
AsyncWebServer server(80);
NetworkManager network(ssid, password, &server);
RandomServo Servo1(18, 12, 170, 200, 2000);

// Status variables
bool isRunning = false;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long startTime = 0;

void setup() {
  if (DEBUG_LEVEL > 0) Serial.begin(115200);

  // Initialize button pin with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  
  network.begin(DEBUG_LEVEL);
  randomSeed(analogRead(34));
  Servo1.begin();

  if (DEBUG_LEVEL >= 1) {
    Serial.println("[SYSTEM] Ready. Press button on GPIO 4 to start.");
    WebSerial.println("[SYSTEM] Ready. Press button to start.");
  }
}

void loop() {
  // 1. KNOP LOGICA (State Change Detection)
  bool currentButtonState = digitalRead(buttonPin);

  // Check of de knop NU is ingedrukt, terwijl hij dat net nog NIET was
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    if (millis() - lastDebounceTime > 50) {
      isRunning = !isRunning;
      lastDebounceTime = millis();
    }
    
    if (isRunning) {
      startTime = millis();
      if (DEBUG_LEVEL >= 1) WebSerial.println("[TIMER] Gestart!");
    } else {
      if (DEBUG_LEVEL >= 1) WebSerial.println("[TIMER] Handmatig gestopt.");
    }
    
    // Een heel korte software-debounce (optioneel, maar vaak niet eens nodig)
    // delay(5) is vaak al genoeg en onmerkbaar.
  }
  // Onthoud de status voor de volgende ronde
  lastButtonState = currentButtonState;

  // 2. RUNTIME LOGICA
  if (isRunning) {
    Servo1.update(DEBUG_LEVEL);

    if (millis() - startTime >= runtimeLimit) {
      isRunning = false;
      if (DEBUG_LEVEL >= 1) WebSerial.println("[TIMER] Tijd is om.");
    }
  }
}