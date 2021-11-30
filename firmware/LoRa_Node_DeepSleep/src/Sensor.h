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


OneWire oneWire(ONE_WIRE_BUS_AND_SDA);
// Wire.begin(ONE_WIRE_BUS_AND_SDA,I2C_SCL);                  // put here the Pins of I2C

class Sensor {
    int _sensorModule;
    String _lastValue = "";

    Adafruit_BME280 bme; // I2C

    public:
        Sensor() {
            pinMode(VCC, OUTPUT);
        }

        void readValues(int sensorModule) {
            switch (sensorModule)
            {
            case 0: {
                DallasTemperature sensors(&oneWire);
                delay(3000);
                digitalWrite(VCC, HIGH);
                sensors.begin();
                sensors.requestTemperatures(); // Send the command to get temperatures  
                Serial.print("Temperature DS18: ");
                Serial.println(sensors.getTempCByIndex(0));  
                _lastValue = String(sensors.getTempCByIndex(0));

                delay(10);
                digitalWrite(VCC, LOW);
            } break;
            case 1: {
                unsigned status;
                status = bme.begin(0x76);  
                if (!status) {
                    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
                    Serial.print("SensorID was: 0x"); 
                    Serial.println(bme.sensorID(),16);
                    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
                    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
                    Serial.print("        ID of 0x60 represents a BME 280.\n");
                    Serial.print("        ID of 0x61 represents a BME 680.\n");
                }
                float pressuare = bme.readPressure() / 100.0F;
                _lastValue = String(bme.readTemperature())+','+String(pressuare)+','+bme.readHumidity();
                break;
            }
            case 2: {
                Adafruit_CCS811 ccs;
                ClosedCube_HDC1080 hdc1080;
                Adafruit_BMP280 bmp280;   

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
                break;
            }
            default:
                break;
            }
        }

        String getLastValue() {
            return _lastValue;
        }
};