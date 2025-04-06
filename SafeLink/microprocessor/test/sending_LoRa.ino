#include <SPI.h>
#include <LoRa.h>

#define SS 5      // LoRa module NSS
#define RST 14    // LoRa module RESET
#define DIO0 26   // LoRa module DIO0

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");

  // Start LoRa module
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) { // Change frequency if needed (e.g., 868E6, 433E6)
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.println("Sending packet...");
  
  LoRa.beginPacket();
  LoRa.print("Hello from ESP32");
  LoRa.endPacket();

  delay(2000); // Send every 2 seconds
}