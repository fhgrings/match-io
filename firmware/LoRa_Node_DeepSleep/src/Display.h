#ifndef _DISPLAY_H_
#define _DISPLAY_H_


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OLED pins

#if defined( heltec )
    #define OLED_SDA 4
    #define OLED_SCL 15 
    #define OLED_RST 16
    #define SOURCE_PIN 36
#else 
    #define SOURCE_PIN 36
    #define OLED_SDA 21
    #define OLED_SCL 22 
    #define OLED_RST 16
#endif

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

int optionsPosY[] = {20, 30, 40, 50};
int optionSelected = 0;
int optionLength = sizeof(optionsPosY);


class Display {
    private:
        int _sourceVoltage = 0;
        String _sensorModule = "Null";
    
    public:
        Display() {
            pinMode(OLED_RST, OUTPUT);
            digitalWrite(OLED_RST, LOW);
            delay(20);
            digitalWrite(OLED_RST, HIGH);
        }

        void init(int sourceVoltage, String sensorModule) {
            _sourceVoltage = sourceVoltage;
            _sensorModule = sensorModule;

            Wire.begin(OLED_SDA, OLED_SCL);
            if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
                Serial.println(F("SSD1306 allocation failed"));
                for(;;); // Don't proceed, loop forever
            }
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setTextSize(1);
            display.setCursor(0,0);
            display.print("Match-IO    Node");
            display.setCursor(10,35);
            display.print("Inicializando...");
            display.display();
        }

        void setSensorModule(String sensorModule) {
            _sensorModule = sensorModule;
        }

        void sleep() {
            display.ssd1306_command(SSD1306_DISPLAYOFF);
        }

        void screenHeader() {
            display.clearDisplay();
            display.setCursor(0,0);
            display.print(String(_sourceVoltage)+ "%");
            display.setCursor(50,0);
            display.print("M-IO");
            display.setCursor(95,0);
            display.print(_sensorModule);
        }

        void menuScreen() {
            screenHeader();
            display.setCursor(10,15);
            display.print("Config Sensor");
            display.setCursor(10,25);
            display.print("Config Posicao");
            display.setCursor(10,35);
            display.print("Modo Producao");
            display.drawCircle(5,optionsPosY[optionSelected], 1, 1);
            display.display();
            delay(10);
        }

        void sensorConfigScreen() {
            screenHeader();
            display.setCursor(10,15);
            display.print("Temp - DS18");
            display.setCursor(10,25);
            display.print("Temp - BME");
            display.setCursor(10,35);
            display.print("Voltar");
            display.drawCircle(5,optionsPosY[optionSelected], 1, 1);
            display.display();
        } 

        void positionConfigScreen(String message, String RSSI) {
            screenHeader();
            display.setCursor(0,15);
            display.print("RSSI: " + RSSI);
            display.setCursor(0,25);
            display.print("Message: " + message);
            display.setCursor(90,45);
            display.print("Voltar");
            display.drawCircle(85, 50, 1, 1);
            display.display();
        }

        void productionScreen(String ID, String refreshRate, String lastMessage) {
            screenHeader();
            display.setCursor(0,15);
            display.print("ID: " + ID);
            display.setCursor(70,15);
            display.print("Att: " + refreshRate);
            display.setCursor(0,25);
            display.print("Valor: ");
            display.setCursor(0,35);
            display.print(lastMessage);
            display.setCursor(90,45);
            display.print("Voltar");
            display.drawCircle(85, 50, 1, 1);
            display.display();
        }
};
#endif // _DISPLAY_H_
