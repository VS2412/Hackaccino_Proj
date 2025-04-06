#include "server.h"
#include "LoRaHandler.h"
#include <ArduinoJson.h>
#include "webpage.h"

#if defined(ESP8266)
  ESP8266WebServer server(80);
#elif defined(ESP32)
  WebServer server(80);
#endif

#include <ctime>

const char *ssid = "ESP8266_AP";
const char *password = "12345678";

String receivedLoRaData = "";
unsigned long receivedLoRaTimestamp = 0;
String username = "default_user";  // Default username

// LoRa module pins (change based on your board)
#define SS 18
#define RST 14
#define DIO0 26

void setupWiFi() {
  IPAddress local_IP(192, 168, 1, 1);  // Custom IP address
  IPAddress gateway(192, 168, 1, 1);   // Gateway (same as local IP for AP mode)
  IPAddress subnet(255, 255, 255, 0);  // Subnet mask

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  Serial.println("Access Point Started!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void setupLoRa() {
  Serial.println("Initializing LoRa...");
  LoRa.setPins(SS, RST, DIO0);
  if (!initLoRa()) {  // Adjust frequency based on your region
    Serial.println("LoRa init failed. Check wiring!");
    while (1);
  }
  Serial.println("LoRa Initialized!");
}

// Get current timestamp (in seconds)
unsigned long getTimestamp() {
  return millis() / 1000;
}

void sendCORSHeaders() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

// Handle CORS preflight requests (OPTIONS method)
void handleCORSOptions() {
    sendCORSHeaders();
    server.send(204);  // No Content response
}



// API Endpoint: Set Username (POST /setuser)
void handleSetUsername() {
  sendCORSHeaders();
  if (server.hasArg("username")) {
    username = server.arg("username");
    Serial.println("Username set to: " + username);
    server.send(200, "application/json", R"({"status": "Username updated"})");
  } else {
    server.send(200, "application/json", R"({"error": "No username provided"})");
  }
}

// API Endpoint: Get LoRa Data (GET /loradata)
void handleLoRaData() {
  sendCORSHeaders();
  if (receivedLoRaData.isEmpty()) {
    server.send(200, "application/json", R"({"message": null})");
  } else {
    StaticJsonDocument<200> jsonResponse;
    jsonResponse["message"] = receivedLoRaData;
    jsonResponse["timestamp"] = receivedLoRaTimestamp;
    jsonResponse["username"] = username;

    String response;
    serializeJson(jsonResponse, response);
    server.send(200, "application/json", response);
  }
}

// API Endpoint: Send LoRa Message (POST /send)
void handleSendLoRaMessage() {
  sendCORSHeaders();
  if (server.hasArg("message")) {
    String message = server.arg("message");
    String fullMessage = username + ": " + message;  // Include username
    Serial.println("Sending LoRa: " + fullMessage);
    
    LoRa.beginPacket();
    LoRa.print(fullMessage);
    LoRa.endPacket();
    
    server.send(200, "application/json", R"({"status": "Message sent"})");
  } else {
    server.send(400, "application/json", R"({"error": "No message provided"})");
  }
}

void handleRoot() {
    server.send(200, "text/html", index_html);
}

void setupServer() {
  setupWiFi();
  setupLoRa();

  server.on("/", HTTP_GET, handleRoot);
  server.on("/setuser", HTTP_POST, handleSetUsername);  // Set username
  server.on("/loradata", HTTP_GET, handleLoRaData);  // Get latest LoRa message (JSON)
  server.on("/send", HTTP_POST, handleSendLoRaMessage);  // Send LoRa message

  server.begin();
  Serial.println("API server started.");
}

void loopLoRaReceiver() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    receivedLoRaData = "";
    while (LoRa.available()) {
      receivedLoRaData += (char)LoRa.read();
    }
    receivedLoRaTimestamp = getTimestamp();  // Update timestamp
    Serial.printf("Received LoRa: %s at %lu seconds\n", receivedLoRaData.c_str(), receivedLoRaTimestamp);
  }
}

void handleClientRequests() {
  server.handleClient();
  loopLoRaReceiver();
}
