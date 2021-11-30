#include <Arduino.h>
#include "Lora.h"

Lora lora;

bool flagLoraMessage = false;

int loraSendMessage = 0;
String UNIQUE_ID;

void getChipID();
void loraCallBack();
void loraLoop();

void setup() {
  Serial.begin(115200);
  getChipID();
  lora.onReceive(loraCallBack);
  lora.init(UNIQUE_ID);
  lora.receive();
  Serial.println("Setup Done!");
}
void loop() {
  delay(10);
  loraLoop();
  delay(1000);
}


void loraLoop() {
  if (flagLoraMessage) {
    flagLoraMessage = false;
    Serial.println("LoRa Loop");
    Serial.println(lora.getPacket());
    delay(1000);
    lora.sendMessage(lora.getPacket());
  }
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

