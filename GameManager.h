#ifndef GameManager_h
#define GameManager_h

#include "Button.h"
#include "LEDLight.h"
#include "Buzzer.h"
#include "Arduino.h"
#include "Bomb.h"

class GameManager
{
  public:
    GameManager(Bomb bomb, Button btnA, Button btnB, Button btnC);

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

    Bomb _bomb; 
    
    Button _btnA; 
    Button _btnB; 
    Button _btnC;

    int _running_step;

    float _game_play_time;
    float _game_play_timer;

    bool _game_started;
    bool _game_ended;
};

#endif
