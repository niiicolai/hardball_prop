#ifndef GameManager_h
#define GameManager_h

#include "Button.h"
#include "LEDLight.h"
#include "Buzzer.h"
#include "Arduino.h"

class GameManager
{
  public:
    GameManager(Buzzer buzzer, LEDLight red, LEDLight yellow, LEDLight green, Button btnA, Button btnB, Button btnC);

    void update();

    void waitForMode();

    void selectMode(int m);

    void runGame();

    void runningMode(LEDLight led, float play_time);

    void explode();

    void defuse();

    void runLedEffect();

    void runLedEffect2();
    
  private:

    Buzzer _buzzer;
    
    LEDLight _red; 
    LEDLight _yellow; 
    LEDLight _green; 
    
    Button _btnA; 
    Button _btnB; 
    Button _btnC;



    int _running_step;

    

    float _game_play_time;
    float _game_play_timer;

    
    
    float _buzz_timer_max;
    float _buzz_timer;



    float _buzz_play_time;
    


    bool _game_started;
    bool _game_ended;
};

#endif
