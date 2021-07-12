#include "Arduino.h"
#include "LEDLight.h"

LEDLight::LEDLight()
{
  
}

LEDLight::LEDLight(int pin)
{
  _pin = pin;
}

void LEDLight::setPinMode()
{
  pinMode(_pin, OUTPUT);
}

void LEDLight::turnOn()
{
  digitalWrite(_pin, HIGH);
}

void LEDLight::turnOff()
{
  digitalWrite(_pin, LOW);
}

void LEDLight::toggle()
{
  digitalWrite(_pin, LOW);
}

bool LEDLight::isOn()
{
  return digitalRead(_pin) == HIGH;
}

bool LEDLight::isOff()
{
  return !LEDLight::isOn();
}
