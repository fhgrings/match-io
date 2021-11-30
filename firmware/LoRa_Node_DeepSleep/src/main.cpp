#include <EEPROM.h>

#include "Display.h"
#include "Lora.h"
#include "Button.h"
#include "Sensor.h"

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
void changeOption();
void selectOption();

void menuState();
void sensorState();
void positionState();
void prodState();

void loadFromMemory();
void deepSleep();

void getChipID();
int getBattVoltage();

void sendLoRaAndSleep();
void selectFlow();

enum screenSelected {
  MENU,
  SENSOR,
  POSITION,
  PROD
};

enum sensorModuleList {
  DS18,
  BME,
  CJMCU
};

enum EpromPosition {
  SENSOR_MODULE,
  REFRESH_RATE,
  PRODUCTION_MODE
};

String sensorModuleNames[3] = {"DS18", "BME", "CJMCU"};
String UNIQUE_ID;

Display disp;
bool isFirstScreenLoad = false;
Lora lora;
Button button;
Sensor sensor;


int machineState = 0;
int sensorModule = 0;

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

  EEPROM.begin(EEPROM_SIZE);

  loadFromMemory();
  getChipID();
  selectFlow();

  button.init(USER_BUTTON, changeOption, selectOption, 1);
  disp.init(getBattVoltage(), sensorModuleNames[sensorModule]);
  disp.menuScreen();

  lora.onReceive(onReceive);
  lora.init(getBattVoltage(),UNIQUE_ID);
  lora.receive();

  esp_sleep_enable_timer_wakeup(refreshRate * uS_TO_S_FACTOR);
  esp_sleep_enable_ext0_wakeup(INTERRUPT_BUTTON, 0); //1 = High, 0 = Low
}

void loop() {
  if (updateRefreshRate) {
    EEPROM.write(REFRESH_RATE, refreshRate);
    EEPROM.commit();
    Serial.println(refreshRate);
  }

  if (isProductionRoutine) {
    sendLoRaAndSleep();
  }
  if (menuTimerToProd >= 6000){
    Serial.println("Entrando em prod");
    isProductionRoutine = true;
    EEPROM.write(PRODUCTION_MODE, isProductionRoutine);
    EEPROM.commit();
  }
  switch (machineState) {
    case MENU: {
      menuState();
    } break;
    case SENSOR: {
      sensorState();
    } break;
    case POSITION: {
      positionState();
    } break;
    case PROD: {
      prodState();
    } break;
    default : {
    } break;
  }
  menuTimerToProd++;
  delay(10);
}

void sendLoRaAndSleep() {
  disp.sleep();
  sensor.readValues(sensorModule);
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
      machineState = PROD;
    } else {
      isProductionRoutine = true;
    }
  } else {
    sendData = 10;
  }
}

void loadFromMemory() {
  sensorModule = EEPROM.read(SENSOR_MODULE);
  refreshRate = EEPROM.read(REFRESH_RATE);
  isProductionMode = EEPROM.read(PRODUCTION_MODE);

  Serial.print("sensorModule: ");
  Serial.println(sensorModule);
  Serial.print("refreshRate: ");
  Serial.println(refreshRate);
  Serial.print("isProductionMode: ");
  Serial.println(isProductionMode);
}

void onReceive() {
  refreshRate = lora.getMessage().toInt();
  updateRefreshRate = true;
}

void changeOption() {
  Serial.println("Change Option");
  updateScreen = true;
}

void selectOption() {
  Serial.println("Select Option");
  optionSelected = (optionSelected + 1)  % optionLength;
  Serial.println(optionSelected);
  isFirstScreenLoad = true;
}

void menuState() {
  disp.menuScreen();
  optionLength = 3;
  if (updateScreen) {
    updateScreen = false;
    if (optionSelected == 0) { machineState = SENSOR; }
    if (optionSelected == 1) { machineState = POSITION; }
    if (optionSelected == 2) { machineState = PROD; }
  }
}

void sensorState() {
  disp.sensorConfigScreen();
  optionLength = 3;
  if (updateScreen) {
    updateScreen = false;
    Serial.println(optionSelected);

    if (optionSelected != (optionLength -1)) {
      sensorModule = optionSelected;
      EEPROM.write(0, sensorModule);
      EEPROM.commit();
      Serial.println(sensorModule);
      disp.setSensorModule(sensorModuleNames[sensorModule]);
    }
    machineState = MENU;
  }
}
void positionState() {
  if (isFirstScreenLoad){
    lora.send301();
    isFirstScreenLoad = false;
  }
  disp.positionConfigScreen(lora.getPacket(), lora.getRSSI());
  optionLength = 1;

  if (updateScreen) { 
    updateScreen = false;
    machineState = MENU;
  }
}

void prodState() {
  optionLength = 1;

  if (sendData > 0) {
    sensor.readValues(sensorModule);
    lora.send101(sensor.getLastValue());
    sendData--;
  }

  if (!isProductionMode){
    isProductionMode = true;
    EEPROM.write(PRODUCTION_MODE, isProductionMode);
    EEPROM.commit();
  }

  disp.productionScreen(UNIQUE_ID, String(refreshRate),  sensor.getLastValue());


  if ( timeUntilSleep <= 0 ) { 
    disp.sleep();
    deepSleep(); 
  }
  timeUntilSleep--;

  delay(1000);

  if (updateScreen) { 
    isProductionMode = false;
    EEPROM.write(PRODUCTION_MODE, isProductionMode);
    EEPROM.commit();

    updateScreen = false;
    machineState = MENU;        
  }
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