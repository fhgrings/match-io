#include <EEPROM.h>

#include "Lora.h"
#include "Button.h"
#include "Sensor.h"
#include "Utils.h"

#if defined( WIFI_LoRa_32_V2 )
    #define LED_PIN 25
    #define USER_BUTTON 0 
    #define INTERRUPT_BUTTON GPIO_NUM_0
#elif defined( Wireless_Stick )
    #define LED_PIN 25
    #define USER_BUTTON 0 
    #define INTERRUPT_BUTTON GPIO_NUM_0
#else
    #define LED_PIN 25
    #define USER_BUTTON 38
    #define INTERRUPT_BUTTON GPIO_NUM_38
#endif
#define EEPROM_SIZE 3
#define uS_TO_S_FACTOR 60000000ULL  /* Conversion factor for micro seconds to seconds */


void onReceive();
void testSignal();

void loadFromMemory();
void deepSleep();
void selectFlow();

void getChipID();
int getBattVoltage();

void sendLoRaAndSleep();

enum EpromPosition {
  REFRESH_RATE,
  PRODUCTION_MODE,
};

String UNIQUE_ID;

bool isFirstScreenLoad = false;
bool loraMessageFlag = false;
Lora lora;
Button button;
Sensor sensor;

int refreshRate;
bool updateRefreshRate = false;

bool isProductionMode = false;
bool isProductionRoutine = false;
int sendData = 5;
int timeUntilSleep = 15;

int menuTimerToProd = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21,22);                  // put here the Pins of I2C

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 1);

  Serial.println("\n\nWeaking up");
  EEPROM.begin(EEPROM_SIZE);

  loadFromMemory();
  getChipID();
  selectFlow();

  button.init(USER_BUTTON, testSignal, testSignal, 1);

  lora.onReceive(onReceive);
  lora.init(getBattVoltage(),UNIQUE_ID);
  lora.receive();

  esp_sleep_enable_timer_wakeup(refreshRate * uS_TO_S_FACTOR);
  esp_sleep_enable_ext0_wakeup(INTERRUPT_BUTTON, 0); //1 = High, 0 = Low
  digitalWrite(LED_PIN, 0);
}

void loop() {
  delay(3000);
  Serial.println("Begin Loop");
  if (loraMessageFlag) {
    loraMessageFlag = false;
    if (lora.getStatus() == 201) {
      refreshRate = lora.getMessage().toInt();
      updateRefreshRate = true;
    }
    if (lora.getStatus() == 300) {
      Util.blink((lora.getRSSI()*(-1)/20), 200);
    }
    isProductionRoutine = true;
  }
  if (updateRefreshRate) {
    EEPROM.write(REFRESH_RATE, refreshRate);
    EEPROM.commit();
    Serial.println(refreshRate);
  }
  if (isProductionRoutine) {
    sendLoRaAndSleep();
  }
  if (menuTimerToProd >= 3000){
    isProductionRoutine = true;
    EEPROM.write(PRODUCTION_MODE, isProductionRoutine);
    EEPROM.commit();
  }
  menuTimerToProd++;
  delay(10);
}

void sendLoRaAndSleep() {
  Util.blink(3, 200);
  sensor.readValues();
  lora.send101(sensor.getLastValue());
  delay(10*1000);
  deepSleep();
}

int getBattVoltage() {
  return random(80,90);
}

void selectFlow() {
esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  if (isProductionMode) {
    if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0) {
      sendData = 1;
    } else {
      isProductionRoutine = true;
    }
  } else {
    sendData = 1;
  }
}

void loadFromMemory() {
  refreshRate = EEPROM.read(REFRESH_RATE);
  isProductionMode = EEPROM.read(PRODUCTION_MODE);
    
  Serial.print("refreshRate: ");
  Serial.println(refreshRate);
  Serial.print("isProductionMode: ");
  Serial.println(isProductionMode);
}

void onReceive() {
  loraMessageFlag = true;
  isProductionRoutine = false;
}

void deepSleep() {
  lora.deepSleep();
  esp_deep_sleep_start();
}

void getChipID() {
  uint8_t baseMac[6];
  esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
  char baseMacChr[4] = {0};
  sprintf(baseMacChr, "%02X%02X", baseMac[4], baseMac[5]);
  UNIQUE_ID = String(baseMacChr);
}

void testSignal() {
  lora.send301();
}
