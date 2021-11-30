#include <Arduino.h>
#include <PubSubClient.h>

#include "Utils.h"

#define TOPICO_SUBSCRIBE "/matchio/1/"    
#define TOPICO_PUBLISH   "/matchio/1/data"    
#define ID_MQTT  "MatchIO-Gateway2"  

const char* BROKER_MQTT = "grings.life"; 
// const char* BROKER_MQTT = "192.168.15.8"; 
// const char* BROKER_MQTT = "35.193.140.139"; 
// const char* BROKER_MQTT = "35.202.231.164"; 
int BROKER_PORT = 1883; 

typedef void (*CustomCallBack)();
CustomCallBack _customCallBack;

void mqtt_callback(char* topic, byte* payload, unsigned int length);

String _mqttPacket;
String _mqttMessage;
String _mqttNodeId;
int _mqttStatus;
PubSubClient MQTT(wifiClient);

class Mqtt {
    private:
        ;
    public:
        Mqtt() {
        }

        void init(WiFiClient espClient)  {
            // MQTT.setClient(espClient);

            MQTT.setServer(BROKER_MQTT, BROKER_PORT);
            MQTT.setCallback(mqtt_callback); 
        }

        void onReceive(CustomCallBack callback) {
            _customCallBack = callback;
        }

        void checkConnection() {
            if (!MQTT.connected())
                connect();
        }

        void connect() {
            while (!MQTT.connected()) {
                Serial.print("* Tentando se conectar ao Broker MQTT: ");
                Serial.println(BROKER_MQTT);
                if (MQTT.connect(ID_MQTT)) 
                {
                    Serial.println("Conectado com sucesso ao broker MQTT!");
                    MQTT.subscribe(TOPICO_SUBSCRIBE);
                    sendMessage("1","/connect/1");
                } 
                else
                {
                    Serial.println("Falha ao reconectar no broker.");
                    Serial.println("Havera nova tentatica de conexao em 2s");
                    delay(2000);
                }
            }
        }

        void sendMessage(String message) {
            MQTT.publish(TOPICO_PUBLISH, (char*) message.c_str());
        }

        void sendMessage(String message, String topic) {
            MQTT.publish((char*) topic.c_str(), (char*) message.c_str());
        }

        String getPacket() {
            return _mqttPacket;
        }

        String getMessage() {
            return _mqttMessage;
        }

        int getStatus() {
            return _mqttStatus;
        }

        String getNodeId() {
            return _mqttNodeId;
        }
};

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    Serial.println("Mensagem MQTT CB: ");
    _mqttPacket = "";
    for(int i = 0; i < length; i++) 
    {
        char c = (char)payload[i];
        _mqttPacket += c;
    }    
    _mqttStatus = Util.splitString(_mqttPacket, '/', 0).toInt();
    if ( _mqttStatus == 101 || _mqttStatus == 102 || _mqttStatus == 201 ) {
        _mqttNodeId = Util.splitString(_mqttPacket, '/', 2);
        _mqttMessage = Util.splitString(_mqttPacket, '/', 3);
        _customCallBack();
    }
    Serial.println("Mensagem MQTT recebida: " + _mqttPacket);
}

