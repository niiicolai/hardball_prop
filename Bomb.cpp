#include "Arduino.h"
#include "Bomb.h"
#include "LEDLight.h"
#include "Buzzer.h"

Bomb::Bomb()
{
  
}

Bomb::Bomb(Buzzer buzzer, LEDLight red, LEDLight yellow, LEDLight green)
{
  _buzzer = buzzer;

  _red = red;
  _yellow = yellow;
  _green = green;

  _light_max = 3;
  _light_index = 0;
  
  _buzz_play_time = 400;
  _buzz_timer_max = 8000;
  _buzz_timer_max_current = _buzz_timer_max;
  _buzz_timer = 0;
}

void Bomb::buzz()
{
  _buzz_timer++;
  if (_buzz_timer >= _buzz_timer_max_current)
  {
    _buzz_timer = 0;
    
    LEDLight led = Bomb::ledByIndex();
    Bomb::toggleAndBuzz(led);
  }
}

void Bomb::toggleAndBuzz(LEDLight led)
{
  led.turnOn();
  _buzzer.playWithDelay(_buzz_play_time);
  _buzzer.stop();
  led.turnOff();
}

void Bomb::increaseSpeed(float increase)
{
  _buzz_timer_max_current -= increase;
  if (_buzz_timer_max_current < 0)
  {
    _buzz_timer_max_current = 0; 
  }
}

void Bomb::nextLight()
{
  _light_index = (_light_index + 1) % _light_max;
}


void Bomb::turnOnAllLights()
{
  _red.turnOn();
  _yellow.turnOn();
  _green.turnOn();
}

void Bomb::defuse()
{
  if (_light_index >= _light_max-1)
  {
    Bomb::defuseEffect();
    _green.turnOn();
  }    
  else
    Bomb::nextLight();
}

void Bomb::explode()
{
  Bomb::explodeEffect();
  _red.turnOn();
}

void Bomb::reset()
{
  _buzz_timer_max_current = _buzz_timer_max;
  _buzz_timer = 0;
  _light_index = 0;
}

LEDLight Bomb::ledByIndex()
{
  if (_light_index == 0)
    return _red;
  else if (_light_index == 1)
    return _yellow;
  else 
    return _green;
}

void Bomb::explodeEffect()
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
  delay(d);
}

void Bomb::defuseEffect()
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
  delay(d);
}
