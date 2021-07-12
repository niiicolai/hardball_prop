#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button
{
  public:
    Button();
    Button(int pin);

    void setPinMode();

    bool isPressed();

  private:

    int _pin;
    

};

#endif
