#include "Arduino.h"
#include "Buzzer.h"

Buzzer::Buzzer()
{
  
}

Buzzer::Buzzer(int pin, float frequency)
{
  _pin = pin;
  _frequency = frequency;
}

void Buzzer::setPinMode()
{
  pinMode(_pin, OUTPUT);
}

void Buzzer::setFrequency(float frequency)
{
  _frequency = frequency;
}

void Buzzer::play()
{
  digitalWrite(_pin, LOW);
}

void Buzzer::playWithDelay(float d)
{
  tone(_pin, _frequency);
  delay(d);
}


void Buzzer::stop()
{
  noTone(_pin);
}

bool Buzzer::isOn()
{
  return digitalRead(_pin) == HIGH;
}

bool Buzzer::isOff()
{
  return !Buzzer::isOn();
}
