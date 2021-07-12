#ifndef Bomb_h
#define Bomb_h

#include "LEDLight.h"
#include "Buzzer.h"

#include "Arduino.h"

class Bomb
{
  public:

    Bomb();
    Bomb(Buzzer buzzer, LEDLight red, LEDLight yellow, LEDLight green);

    void buzz();

    void toggleAndBuzz(LEDLight led);

    void increaseSpeed(float increase);

    void nextLight();

    void defuse();

    void explode();

    void turnOnAllLights();

    void reset();

    LEDLight Bomb::ledByIndex();

    void explodeEffect();

    void defuseEffect();

  private:

    Buzzer _buzzer;
    
    LEDLight _red;
    LEDLight _yellow;
    LEDLight _green;

    int _light_max;
    int _light_index;

    float _buzz_play_time;
    float _buzz_timer_max_current;
    float _buzz_timer_max;
    float _buzz_timer;

};

#endif
