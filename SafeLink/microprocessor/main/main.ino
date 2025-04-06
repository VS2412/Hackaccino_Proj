#include "server.h"

void setup() {
  Serial.begin(115200);
  setupServer();  // Initialize the web server
}

void loop() {
  handleClientRequests();  // Handle incoming requests
}