#include <SPI.h>
#include <LoRa.h>

#define BAND 433E6

// Heltec
// #define SCK 5
// #define MISO 19
// #define MOSI 27
// #define SS 18
// #define RST 14
// #define DIO0 26

// ESP32
#define SS 5
#define RST 14
#define DIO0 2

typedef void (*customCallBack)();
customCallBack _customCB;

String _rssi = "null";
String _packSize = "--";
String _packet;

String _message;
String _nodeID;
int _status;


String _UNIQUE_ID;

void defaultCallBack(int packetSize) {
    _packet ="";
    _packSize = String(packetSize,DEC);
    for (int i = 0; i < packetSize; i++) { _packet += (char) LoRa.read(); }
    _customCB();
}

class Lora {
    public: 
        Lora() {
            SPI.begin(SCK, MISO, MOSI, SS);
            LoRa.setPins(SS, RST, DIO0);
            LoRa.onReceive(defaultCallBack);
        }

        void init(String UNIQUE_ID) {
            _UNIQUE_ID = UNIQUE_ID;
            if (!LoRa.begin(BAND)) {
                Serial.println("Starting LoRa failed!");
                delay(10000);
                ESP.restart();
            }
        }

        void onReceive(customCallBack customCB) {
            _customCB = customCB;
        }

        void receive() {
            LoRa.receive();
        }

        void sendMessage(String message) {
            LoRa.beginPacket();
            LoRa.setTxPower(14);
            LoRa.print(message);
            LoRa.endPacket();
            LoRa.receive();
        }

        void deepSleep() {
            LoRa.end();
            LoRa.sleep();
            delay(10);
        }

        String getPacket() {
            return _packet;
        }

        String getMessage() {
            return _message;
        }

        int getStatus() {
            return _status;
        }

        String getNodeId() {
            return _nodeID;
        }

        String getRSSI() {
            return _rssi;
        }
};

