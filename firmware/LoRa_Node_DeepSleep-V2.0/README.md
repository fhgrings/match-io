board = heltec_wireless_stick
board = ttgo-t-beam
board = heltec_wifi_lora_32_V2


### platform.ini
```
; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[env:heltec]
platform = espressif32
board = heltec_wireless_stick
framework = arduino
monitor_speed = 115200
upload_port = /dev/ttyUSB1
lib_deps = 
	sandeepmistry/LoRa @ ^0.8.0
	adafruit/Adafruit GFX Library @ ^1.10.3
	adafruit/Adafruit SSD1306 @ ^2.4.1
	adafruit/Adafruit BusIO @ ^1.7.0
	adafruit/Adafruit BME280 Library @ ^2.1.2
	milesburton/DallasTemperature @ ^3.9.1
	paulstoffregen/OneWire @ ^2.3.5
	adafruit/Adafruit BMP280 Library @ ^2.3.0
	adafruit/Adafruit CCS811 Library @ ^1.0.5
	closedcube/ClosedCube HDC1080 @ ^1.3.2
```