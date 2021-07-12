#include "Button.h"
#include "LEDLight.h"
#include "Buzzer.h"
#include "Arduino.h"
#include "GameManager.h"


GameManager::GameManager(Buzzer buzzer, LEDLight red, LEDLight yellow, LEDLight green, Button btnA, Button btnB, Button btnC)
{
  _buzzer = buzzer;

  _red = red;
  _yellow = yellow;
  _green = green;
  
  _btnA = btnA;
  _btnB = btnB;
  _btnC = btnC;

  _game_started = false;
  _game_ended = false;
  _running_step = 0;
  _game_play_time = 30000;
  _buzz_play_time = 400;

  _game_play_time = 30000;
  _game_play_timer = 0;
  
  _buzz_timer_max = 8000;
  _buzz_timer = 0;
}

void GameManager::update()
{
  if (_game_ended)
  {
    if (_btnA.isPressed())
    {
      _game_ended = false;
      _game_started = false;
      _game_play_timer = 0;
      _buzz_timer = 0;
      delay(1000);
      return;
    }
  }
  else
  {
    if (_game_started)
      GameManager::runGame();
    else
      GameManager::waitForMode();
  }
}

void GameManager::waitForMode()
{
  _red.turnOn();
  _yellow.turnOn();
  _green.turnOn();

  if (_btnA.isPressed())
    GameManager::selectMode(0);
  else if (_btnB.isPressed())
    GameManager::selectMode(1);
  else if (_btnC.isPressed())
    GameManager::selectMode(2);
}

void GameManager::selectMode(int m)
{
  GameManager::runLedEffect2();

  if (m == 0)
    _game_play_time = 30000;
  else if (m == 1)
    _game_play_time = 150000;
  else if (m == 2)
    _game_play_time = 300000;

  _game_started = true;
}

void GameManager::runGame()
{

  // Game play timer
  _game_play_timer++;
  if (_game_play_timer >= _game_play_time)
  {
    _game_play_timer = 0;
    GameManager::explode();
    return;
  }

  float between_buzz = _buzz_timer_max;
  if (_game_play_time/_game_play_timer > 0.7)
  {
    between_buzz = _buzz_timer_max/3;
  }
  else if (_game_play_time/_game_play_timer > 0.5)
  {
    between_buzz = _buzz_timer_max/2;
  }

  // Buzz game timer
  _buzz_timer++;
  if (_buzz_timer >= between_buzz)
  {
    _buzz_timer = 0;

    if (_running_step == 0)
      GameManager::runningMode(_red, _buzz_play_time);
    else if (_running_step == 1)
      GameManager::runningMode(_yellow, _buzz_play_time);
    else if (_running_step == 2)
      GameManager::runningMode(_green, _buzz_play_time);
  }

  if (_running_step == 0 && _btnC.isPressed())
    _running_step = 1;
  else if (_running_step == 1 && _btnB.isPressed())
    _running_step = 2;
  else if (_running_step == 2 && _btnA.isPressed())
    GameManager::defuse();
}

void GameManager::runningMode(LEDLight led, float play_time)
{
  led.turnOn();
  _buzzer.playWithDelay(play_time);
  _buzzer.stop();
  led.turnOff();
}

void GameManager::explode()
{
  GameManager::runLedEffect();
  GameManager::runLedEffect();

  _red.turnOn();
  
  _running_step = 0;
  _game_ended = true;
}

void GameManager::defuse()
{
  GameManager::runLedEffect2();

  _green.turnOn();
  
  _running_step = 0;
  _game_ended = true;
}

void GameManager::runLedEffect()
{
  float d = 400;
  
  _green.turnOn();
  _buzzer.setFrequency(300);
  _buzzer.playWithDelay(d);

  _yellow.turnOn();
  _buzzer.setFrequency(400);
  _buzzer.playWithDelay(d);

  _red.turnOn();
  _buzzer.setFrequency(500);
  _buzzer.playWithDelay(d);

  _green.turnOff();
  _buzzer.setFrequency(400);
  _buzzer.playWithDelay(d);

  _yellow.turnOff();
  _buzzer.setFrequency(300);
  _buzzer.playWithDelay(d);

  _red.turnOff();
  _buzzer.stop();
}

void GameManager::runLedEffect2()
{
  float d = 400;
  
  _green.turnOn();
  delay(d);

  _yellow.turnOn();
  delay(d);
  
  _red.turnOn();
  delay(d);
  
  _green.turnOff();
  delay(d);
  
  _yellow.turnOff();
  delay(d);
  
  _red.turnOff();
}
