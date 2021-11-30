#ifndef UTILS_H
#define UTILS_H

#define LED_PIN 14

class Utils
{
private:
    
public:
    Utils() {
        pinMode(LED_PIN, OUTPUT);
    };
    static void blink (int repeat, int delayMls) {
        for (int i=0; i<repeat; i++) {
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
            delay(delayMls/2);
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
            delay(delayMls/2);
        }
    }

    static void ledOff() {
        digitalWrite(LED_PIN, LOW);
    }

    static String splitString(String data, char separator, int index) {
        int found = 0;
        int strIndex[] = {0, -1};
        int maxIndex = data.length()-1;

        for(int i=0; i<=maxIndex && found<=index; i++){
            if(data.charAt(i)==separator || i==maxIndex){
                found++;
                strIndex[0] = strIndex[1]+1;
                strIndex[1] = (i == maxIndex) ? i+1 : i;
            }
        }
        return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
    }

    
};

extern Utils Util;


#endif