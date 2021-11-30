#include <Arduino.h>

#include "Wifi.h"
#include "Mqtt.h"
#include "Lora.h"
#include "Utils.h"

#define pendingMessagesSize 10

Wifi wifi;
Mqtt mqtt;
Lora lora;

bool flagLoraMessage = false;
bool flagMqttMessage = false;

int loraSendMessage = 0;

String pendingMessages[pendingMessagesSize][2];

String UNIQUE_ID;

void mqttCallBack();
void loraCallBack();
void sendLoraToNode();
void loraLoop();
void mqttLoop();
void sendLoRaToNode();



void setup() {
  for (int i=pendingMessagesSize-1; i>0; i--) {
    pendingMessages[i][0] = "";
    pendingMessages[i][1] = "";
  }
  Serial.begin(115200);
  wifi.init();
  mqtt.init(wifi.getClient());
  mqtt.onReceive(mqttCallBack);
  mqtt.checkConnection();

  lora.onReceive(loraCallBack);
  lora.init(UNIQUE_ID);
  lora.receive();
  Serial.println("Setup Done!");
}
void loop() {
  delay(10);
  // Serial.println("init Loop");
  wifi.checkConnection();
  mqtt.checkConnection();

  loraLoop();
  mqttLoop();

  delay(1000);
}

void mqttLoop() {
  if (flagMqttMessage) {
    // Util.blink(2, 200);
    Serial.println("Mqtt Loop");
    for (int i=pendingMessagesSize-1; i>0; i--) {
      if (pendingMessages[i][0] == "") {
        pendingMessages[i][0] = mqtt.getNodeId();
        pendingMessages[i][1] = mqtt.getPacket();
        break;
      }
    }
    for (int i=pendingMessagesSize-1; i>0; i--) {
      Serial.println(String(i) + "-" + pendingMessages[i][0]);
    }
    flagMqttMessage = false;
  }
  MQTT.loop();
}

void loraLoop() {
  if (flagLoraMessage) {
    // Util.blink(4, 200);
    flagLoraMessage = false;
    Serial.println("LoRa Loop");
    Serial.println(lora.getPacket());
    Serial.println(String(lora.getStatus()));

    switch (lora.getStatus())
    {
    case 101:
      Serial.println("Status: 101");
      Serial.println("Send MQTT");
      mqtt.sendMessage(String(lora.getPacket() + "/" + lora.getRSSI()));
      sendLoRaToNode();
      break;
    case 301:
      loraSendMessage = 1;
      break;    
    default:
      break;
    }
  }

  if (loraSendMessage > 0) {
    lora.send300(String(loraSendMessage));
    loraSendMessage--;
  }
  return;
}

void sendLoRaToNode() {
  String idNode = lora.getNodeId();
  for (int i=pendingMessagesSize-1; i>0; i--) {
    if (pendingMessages[i][0] == idNode) {
      lora.send201(mqtt.getPacket());
      pendingMessages[i][0] = "";
      pendingMessages[i][1] = "";
    }
  }
}

void mqttCallBack() {
  flagMqttMessage = true;
  return;
}

void loraCallBack() {
  flagLoraMessage = true;
  return;
}

void getChipID() {
  uint8_t baseMac[6];
  esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
  char baseMacChr[4] = {0};
  sprintf(baseMacChr, "%02X%02X", baseMac[4], baseMac[5]);
  UNIQUE_ID = String(baseMacChr);
}

