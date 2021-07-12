#ifndef LEDLight_h
#define LEDLight_h

#include "Arduino.h"

class LEDLight
{
  public:
    LEDLight();
    LEDLight(int pin);

    void setPinMode();

    void turnOn();

    void turnOff();

    void toggle();

    bool isOn();

    bool isOff();

  private:

    int _pin;

};

#endif
