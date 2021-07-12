#include "Arduino.h"
#include "Button.h"

Button::Button()
{
}

Button::Button(int pin)
{
  _pin = pin;
}

void Button::setPinMode()
{
  pinMode(_pin, INPUT_PULLUP);
}

bool Button::isPressed()
{
  return digitalRead(_pin) == LOW;
}
