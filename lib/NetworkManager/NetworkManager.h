#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

class NetworkManager {
  private:
    const char* _ssid;
    const char* _password;
    AsyncWebServer* _server;
    void (*_msgCallback)(uint8_t*, size_t);

  public:
    NetworkManager(const char* ssid, const char* password, AsyncWebServer* server);
    void begin(int logLevel = 0);
    void setMsgCallback(void (*callback)(uint8_t*, size_t));
};

#endif
