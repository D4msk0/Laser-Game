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

  public:
    NetworkManager(const char* ssid, const char* password, AsyncWebServer* server);
    void begin(int logLevel = 1);
};

#endif
