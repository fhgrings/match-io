#include <SPI.h>
#include <LoRa.h>

#define BAND 433E6

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

typedef void (*customCallBack)();
customCallBack _customCB;

String _rssi = "null";
String _packSize = "--";
String _packet;
String _message;
int _status;

String _UNIQUE_ID;
int _battVoltage;

String splitString(String data, char separator, int index);


void defaultCallBack(int packetSize) {
    String ID;
    String data;

    _packet ="";
    _packSize = String(packetSize,DEC);
    for (int i = 0; i < packetSize; i++) { _packet += (char) LoRa.read(); }
    Serial.println("defautlCB: " +_packet);
    _status = splitString(_packet, '/', 0).toInt();
    ID = splitString(_packet, '/', 2);
    data = splitString(_packet, '/', 3);
    Serial.println(_status);
    Serial.print(ID);
    Serial.println(_UNIQUE_ID);
    Serial.println(data);

    if ( _status == 201 && ID == _UNIQUE_ID) {
        _message = data;
        _customCB();
        return;
    }
    if (_status == 300) {
        _message = data;
        _customCB();
        return;
    }

}

class Lora {
    public: 
        Lora() {
            SPI.begin(SCK, MISO, MOSI, SS);
            LoRa.setPins(SS, RST, DIO0);
            LoRa.onReceive(defaultCallBack);

        }

        void init(int battVoltage, String UNIQUE_ID) {
            _UNIQUE_ID = UNIQUE_ID;
            _battVoltage = battVoltage;
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
            // LoRa.setSpreadingFactor(10);
            LoRa.setTxPower(17);
            String msg = "101/" + String(random(100)) + "/" + _UNIQUE_ID + "/" + _battVoltage + ","+ message;
            LoRa.beginPacket();
            LoRa.print(msg);
            LoRa.endPacket();
            LoRa.receive();
            Serial.println("Sent LoRa: " + msg);
        }

        void send301() {
            Serial.println("Iniciando301");
            LoRa.beginPacket();
            LoRa.setTxPower(14);
            LoRa.print("301/" + String(random(100)));
            LoRa.endPacket();
            LoRa.receive();
            Serial.println("send301/");
        }

        // https://stackoverflow.com/questions/9072320/split-string-into-string-array


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

        int getRSSI() {
            return LoRa.packetRssi();
        }
        
        int getStatus() {
            return _status;
        }

};


String splitString(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length()-1;

    for(int i=0; i<=maxIndex && found<=index; i++){
        if(data.charAt(i)==separator || i==maxIndex){
            found++;
            strIndex[0] = strIndex[1]+1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}