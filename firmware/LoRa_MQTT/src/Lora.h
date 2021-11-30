#include <SPI.h>
#include <LoRa.h>

#include "Utils.h"

#define BAND 433E6

// Heltec
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

// ESP32
// #define SS 5
// #define RST 14
// #define DIO0 2

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
    _rssi = String(LoRa.packetRssi(), DEC);
    Serial.println("defautlCB: " +_packet);

    _status = Util.splitString(_packet, '/', 0).toInt();
    
    if ( _status == 101 || _status == 102 || _status == 201 ) {
        _nodeID = Util.splitString(_packet, '/', 2);
        _message = Util.splitString(_packet, '/', 3);
    }
    Serial.println("Mensagem LoRa recebida: " + _packet);


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
                while (1);
            }
        }

        void onReceive(customCallBack customCB) {
            _customCB = customCB;
        }

        void receive() {
            LoRa.receive();
        }

        void send101(String message) {
            LoRa.beginPacket();
            LoRa.setTxPower(14);
            LoRa.print("101/" + String(random(100)) + "/" + _UNIQUE_ID + "/" + message);
            LoRa.endPacket();
            LoRa.receive();
            Serial.println("Sent 101" + message);
        }

        void send201(String message) {
            LoRa.beginPacket();
            LoRa.setTxPower(14);
            LoRa.print(message);
            LoRa.endPacket();
            LoRa.receive();
        }

        void send300(String message) {
            LoRa.beginPacket();
            LoRa.setTxPower(14);
            LoRa.print("300/" + String(random(100)) + "/" + message);
            LoRa.endPacket();
            LoRa.receive();
        }

        void send301() {
            LoRa.beginPacket();
            LoRa.setTxPower(14);
            LoRa.print("301/" + String(random(100)));
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

