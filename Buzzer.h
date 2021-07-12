#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"

class Buzzer
{
  public:
    Buzzer();
    Buzzer(int pin, float frequency);

    void setPinMode();

    void setFrequency(float frequency);

    void play();

    void playWithDelay(float d);

    void stop();

    bool isOn();

    bool isOff();
    
  private:

    int _pin;

    float _frequency;

};

#endif
