#include "Button.h"
#include "LEDLight.h"
#include "Buzzer.h"
#include "Arduino.h"
#include "GameManager.h"
#include "Bomb.h"


GameManager::GameManager(Bomb bomb, Button btnA, Button btnB, Button btnC)
{
  _bomb = bomb;
  
  _btnA = btnA;
  _btnB = btnB;
  _btnC = btnC;

  _game_started = false;
  _game_ended = false;
  _running_step = 0;

  _game_play_time = 30000;
  _game_play_timer = 0;
}

void GameManager::update()
{
  if (_game_ended)
  {
    if (_btnA.isPressed() ||
        _btnB.isPressed() ||
        _btnC.isPressed())
    {
      _game_ended = false;
      _game_started = false;
      _game_play_timer = 0;
      _bomb.reset();
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
  _bomb.turnOnAllLights();

  if (_btnA.isPressed())
    GameManager::selectMode(0);
  else if (_btnB.isPressed())
    GameManager::selectMode(1);
  else if (_btnC.isPressed())
    GameManager::selectMode(2);
}

void GameManager::selectMode(int m)
{
  _bomb.defuseEffect();

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

  _game_play_timer++;
  if (_game_play_timer >= _game_play_time)
  {
    _game_play_timer = 0;
    _bomb.explode();
    _running_step = 0;
    _game_ended = true;
    return;
  }

  _bomb.buzz();

  if (_running_step == 0 && _btnC.isPressed())
  {
    _bomb.defuse();
    _running_step = 1;
  }
  else if (_running_step == 1 && _btnB.isPressed())
  {
    _bomb.defuse();
    _running_step = 2;
  }
  else if (_running_step == 2 && _btnA.isPressed())
  {
    _bomb.defuse();
    _running_step = 0;
    _game_ended = true;
  }
}
