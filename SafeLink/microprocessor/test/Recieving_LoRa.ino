#include <SPI.h>
#include <LoRa.h>

// Define LoRa module pins
#define SS 15     // D8
#define RST 0     // D3
#define DIO0 4    // D2

void setup() {
    Serial.begin(115200);
    while (!Serial);
    
    Serial.println("LoRa SX1278 Test");

    // Initialize SPI LoRa module
    LoRa.setPins(SS, RST, DIO0);
    
    if (!LoRa.begin(433E6)) { // Set frequency (433 MHz)
        Serial.println("LoRa initialization failed!");
        while (1);
    }

    Serial.println("LoRa initialized successfully.");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Received packet: ");
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.println();
    }
}