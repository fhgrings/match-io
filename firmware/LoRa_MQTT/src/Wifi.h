#include <WiFi.h> 

#include "Utils.h"

WiFiClient wifiClient;

class Wifi
{
private:
    // char* SSID = "Redmi";
    // char* PASSWORD = "felipehg";
    // char* SSID = "HughesNet_D46E0E";
    // char* PASSWORD = "4n4.Cl4r4";
    char* SSID = "VIVOFIBRA-7517";
    char* PASSWORD = "vwJg5wCUvT";
public:
    Wifi(){}

    void init() {
        WiFi.begin(SSID, PASSWORD);
        connect();
    }

    WiFiClient getClient() {
        return wifiClient;
    }

    void checkConnection() {
        if (WiFi.status() == WL_CONNECTED)
            return;
        connect();
    }

    void connect() {
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
            // Util.blink(1, 100);
        }
        Util.ledOff();

        Serial.println();
        Serial.print("Conectado com sucesso na rede ");
        Serial.print(SSID);
        Serial.println("IP obtido: ");
        Serial.println(WiFi.localIP());
    }
};


