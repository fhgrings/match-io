
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Arduino.h"


typedef void (*CallBack)();


int _buttonPin;
long pressedTimer;
bool isButtonPressed = false;
int counter;
bool updateScreen;
double _threashHoldTimer;

CallBack _earlyReleased;
CallBack _longReleased;


void buttonPressed() {
    delay(10);
    if (!digitalRead(_buttonPin)) {
        pressedTimer = millis();
    } else {
        if( (millis() - pressedTimer) > 50) {
            if ( (millis() - pressedTimer) > (_threashHoldTimer * 1000) ) { _earlyReleased(); }
            else { _longReleased(); }
        } 
    }
}

class Button {
public:
  Button() {
    
  }

  void init(int buttonPin, CallBack earlyReleased, CallBack longReleased, double threashHoldTimer) {
    _buttonPin = buttonPin;
    _earlyReleased = earlyReleased;
    _longReleased = longReleased;
    _threashHoldTimer = threashHoldTimer;
    pinMode(buttonPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(_buttonPin), buttonPressed, CHANGE);
  }
};

#endif // _BUTTON_H_

