#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "Adafruit_CCS811.h"
#include "Adafruit_BMP280.h"
#include "ClosedCube_HDC1080.h"

#include <OneWire.h>
#include <DallasTemperature.h>

#define VCC 0
#define ONE_WIRE_BUS_AND_SDA 4
#define I2C_SCL 15

class Sensor {
    int _sensorModule;
    String _lastValue = "";
    
    Adafruit_BME280 bme; // I2C
    
    Adafruit_CCS811 ccs;
    ClosedCube_HDC1080 hdc1080;
    Adafruit_BMP280 bmp280;   

    public:
        Sensor() {
            // pinMode(VCC, OUTPUT);
        }
        void readValues() {
            if (bme.begin(0x76)) {
                delay(3000);
                float pressuare = bme.readPressure() / 100.0F;
                _lastValue = String(bme.readTemperature())+','+String(pressuare)+','+bme.readHumidity();
                return;
            }
            
            hdc1080.begin(0x40);
            bmp280.begin(0x76);  
            ccs.begin();

            delay(5000);

            float pressuare = bmp280.readPressure() / 100.0F;
            float co2 = 0;
            float tvoc = 0;
            if(ccs.available()){
                if(!ccs.readData()){
                Serial.print("CO2: ");
                co2 = ccs.geteCO2();
                Serial.print(co2);
                Serial.print("ppm, TVOC: ");
                tvoc = ccs.getTVOC();
                Serial.println(tvoc);
                }
            }

            _lastValue = String(bmp280.readTemperature())+','+String(pressuare)+','+hdc1080.readHumidity()+','+co2+','+tvoc;
            return;
        }

        String getLastValue() {
            return _lastValue;
        }
};