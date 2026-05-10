#include "NetworkManager.h"

NetworkManager::NetworkManager(const char* ssid, const char* password, AsyncWebServer* server) 
  : _ssid(ssid), _password(password), _server(server) {}

void NetworkManager::begin(int logLevel) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (logLevel > 0) Serial.print(".");
  }

  WebSerial.begin(_server);
  _server->begin();
  ArduinoOTA.begin();

  if (logLevel >= 1) {
    Serial.println("\n[SYSTEM] WiFi verbonden!");
    Serial.print("[SYSTEM] IP-adres: ");
    Serial.println(WiFi.localIP());
  }
}

void NetworkManager::update() {
  ArduinoOTA.handle();
}
