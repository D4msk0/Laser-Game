#include <Arduino.h>
#include <ESP32Servo.h>

// const int LED_PIN = 2; // Built-in LED on ESP32 DOIT DEVKIT V1
Servo servo;
int servoPin = 18; // GPIO pin connected to the servo signal wire

void randomServo(int start, int end);

//Servo minimum angle 12 degrees, maximum angle 170 degrees
int angleMin = 12;
int angleMax = 170;
int minWait = 200;  // Minimale rusttijd in ms
int maxWait = 2000; // Maximale rusttijd in ms (2 seconden)

// Var for timer
unsigned long prevTime = 0;
unsigned long interval = 0;

void setup() {
  Serial.begin(9600);
  // pinMode(LED_PIN, OUTPUT);
  servo.attach(servoPin);

  randomSeed(analogRead(34));
  interval = random(minWait, maxWait);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - prevTime >= interval) {
    randomServo(angleMin, angleMax);
    prevTime = currentTime;
    interval = random(minWait, maxWait);
  }
}

void randomServo(int start, int end) {
  int randomAngle = random(start, end + 1);
  servo.write(randomAngle);
  
  Serial.print("New angle: ");
  Serial.println(randomAngle);
  Serial.print("Next change in: ");
  Serial.print(interval);
  Serial.println(" ms");
}
