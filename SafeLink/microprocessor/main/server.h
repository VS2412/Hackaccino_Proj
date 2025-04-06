#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <Arduino.h>

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  extern ESP8266WebServer server;
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WebServer.h>
  extern WebServer server;
#endif

void setupServer();
void handleClientRequests();

#endif // SERVER_HANDLER_H
