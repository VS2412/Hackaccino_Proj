# **LoRa Mesh Chat**  
**Send text messages without a mobile network using LoRa and ESP32/ESP8266**  

## **Overview**  
LoRa Mesh Chat is a communication system that allows users to send text messages without relying on traditional mobile networks or the internet. It uses an ESP32 or ESP8266 microcontroller with a LoRa module to create a Wi-Fi Access Point (AP). Users can connect via their mobile phones or computers and access a chat interface at `192.168.1.1` to send and receive messages over LoRa.  

## **Features**  
✅ **Offline Communication** – No mobile network or internet required.  
✅ **Wi-Fi Hotspot** – ESP32/ESP8266 creates a local Wi-Fi AP.  
✅ **Web-based Chat Interface** – Accessible at `192.168.1.1`.  
✅ **LoRa-based Messaging** – Messages are transmitted over long distances using LoRa.  
✅ **Multi-User Support** – Multiple devices can connect to the ESP for messaging.  
✅ **Timestamped Messages** – Each message includes a timestamp to avoid duplication.  

## **How It Works**  
1. The ESP32/ESP8266 creates a Wi-Fi AP.  
2. Users connect to the AP from their mobile devices or computers.  
3. A web-based chat interface is available at `192.168.1.1`.  
4. Users send messages, which are transmitted via LoRa.  
5. Incoming messages are displayed on the chat interface.  

## **Hardware Requirements**  
- ESP32 or ESP8266  
- LoRa Module (SX1276/SX1278)  
- Power source (battery or USB)  
- Mobile phone or computer for accessing the chat interface  

## **Software Requirements**  
- Arduino IDE or PlatformIO  
- ESPAsyncWebServer library  
- LoRa library (RadioHead or Arduino-LoRa)  
- WebSocket support for real-time messaging  

## **Installation & Setup**  

### **1. Flash the ESP32/ESP8266**  
1. Install the required libraries in the Arduino IDE.  
2. Flash the firmware onto the ESP32/ESP8266.  

### **2. Connect to Wi-Fi AP**  
1. Power on the ESP32/ESP8266.  
2. Connect to the Wi-Fi AP (default SSID: `LoRaChat`).  
3. Open a browser and go to `192.168.1.1`.  

### **3. Start Chatting!**  
- Type a message and send it.  
- The message is transmitted over LoRa to other devices in the network.  
- Incoming messages are displayed in real time.  

## **Future Enhancements**  
🔹 **Mesh Networking** – Enable multi-hop communication for extended range.  
🔹 **Encryption** – Secure messages with AES encryption.  
🔹 **Message Persistence** – Store messages in flash memory.  
🔹 **Mobile App** – A dedicated Android/iOS app for better user experience.  

## **License**  
This project is open-source under the MIT License. Feel free to contribute!  
