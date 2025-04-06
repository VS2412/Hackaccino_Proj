#ifndef LORA_HANDLER_H
#define LORA_HANDLER_H

#include <SPI.h>
#include <LoRa.h>

// Define LoRa module pins based on board type
#ifdef ESP32
    #define SS 5
    #define RST 14
    #define DIO0 26
#elif defined(ESP8266)
    #define SS 15
    #define RST 0
    #define DIO0 4
#else
    #error "Unsupported board! Use ESP32 or ESP8266."
#endif

// Function to initialize LoRa
bool initLoRa(long frequency = 433E6) {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("Initializing LoRa...");

    LoRa.setPins(SS, RST, DIO0);
    if (!LoRa.begin(frequency)) {
        Serial.println("LoRa initialization failed!");
        return false;
    }

    Serial.print("LoRa initialized at frequency: ");
    Serial.println(frequency);
    return true;
}

// Function to send a message via LoRa
void sendLoRaMessage(const String& message) {
    Serial.println("Sending: " + message);
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
}

// Function to receive a message via LoRa
String receiveLoRaMessage() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        String received = "";
        while (LoRa.available()) {
            received += (char)LoRa.read();
        }
        Serial.println("Received: " + received);
        return received;
    }
    return "";
}

// Function to change the LoRa frequency dynamically
bool setLoRaFrequency(long newFrequency) {
    LoRa.sleep(); // Put LoRa into sleep mode before changing frequency
    if (!LoRa.begin(newFrequency)) {
        Serial.println("Failed to change LoRa frequency!");
        return false;
    }

    Serial.print("LoRa frequency changed to: ");
    Serial.println(newFrequency);
    return true;
}

#endif
