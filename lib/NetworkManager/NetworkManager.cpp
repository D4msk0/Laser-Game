#include "NetworkManager.h"

NetworkManager::NetworkManager(const char* ssid, const char* password, AsyncWebServer* server) 
  : _ssid(ssid), _password(password), _server(server) {}

void (*_msgCallback)(uint8_t*, size_t) = nullptr;

// Function to set the message callback
void NetworkManager::setMsgCallback(void (*callback)(uint8_t*, size_t)) {
  _msgCallback = callback;
}

void NetworkManager::begin(int logLevel) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (logLevel > 0) Serial.print(".");
  }

  // De juiste manier voor nieuwere WebSerial versies:
  WebSerial.begin(_server);
  WebSerial.msgCallback([](uint8_t *data, size_t len) {
    if (_msgCallback) _msgCallback(data, len);
  });
  _server->begin();


  if (logLevel >= 1) {
    Serial.println("\n[SYSTEM] WiFi connected!");
    Serial.print("[SYSTEM] IP-adres: ");
    Serial.println(WiFi.localIP());
  }
}