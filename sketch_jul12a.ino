#include "Button.h"
#include "LEDLight.h"
#include "Buzzer.h"
#include "GameManager.h"

// BUTTONS
Button btnA = Button(9);
Button btnB = Button(10);
Button btnC = Button(11);

// LED(s)
LEDLight greenLED = LEDLight(4);
LEDLight yellowLED = LEDLight(5);
LEDLight redLED = LEDLight(6);

// BUZZERS
Buzzer buzzer = Buzzer(13, 300);

// GAME SETTINGS
GameManager gm = GameManager(buzzer, redLED, yellowLED, greenLED, btnA, btnB, btnC);

float time_between_buzz = 8000;
float timer_buzz = 0;

bool game_started = false;
int defuse_step = 0;


void setup() {
  btnA.setPinMode();
  btnB.setPinMode();
  btnC.setPinMode();

  greenLED.setPinMode();
  yellowLED.setPinMode();
  redLED.setPinMode();

  buzzer.setPinMode();

  gm.runLedEffect2();
  
  Serial.begin(9600);
  while(!Serial) {}
}

void loop() {

  gm.update();
  return;
  
  if (!game_started)
  {
    greenLED.turnOn();
    yellowLED.turnOn();
    redLED.turnOn();

    if (btnA.isPressed())
    {
      game_started = true;
      greenLED.turnOff();
      yellowLED.turnOff();
      redLED.turnOff();
    }
  }
  else
  {
    timer_buzz++;
    if (timer_buzz >= time_between_buzz)
    {
      timer_buzz = 0;
     
      if (defuse_step == 0)
      {
        redLED.turnOn();
        buzzer.playWithDelay(400);
        buzzer.stop();
        redLED.turnOff();
        
      }
      else if (defuse_step == 1)
      {
        yellowLED.turnOn();
        buzzer.playWithDelay(400);
        buzzer.stop();
        yellowLED.turnOff();
      }
      else if (defuse_step == 2)
      {
        greenLED.turnOn();
        buzzer.playWithDelay(400);
        buzzer.stop();
        greenLED.turnOff();
      }
    }

    if (defuse_step == 0 && btnC.isPressed())
    {
      defuse_step = 1;
    }
    else if (defuse_step == 1 && btnB.isPressed())
    {
      defuse_step = 2;
    }
    else if (defuse_step == 2 && btnA.isPressed())
    {
      endGame();
    }
  }
}

void endGame()
{
  SwitchLEDLoopSound(150);
  defuse_step = 0;
  game_started = false;
}

void SwitchLEDLoop(float d)
{
  greenLED.turnOn();
  delay(d);

  yellowLED.turnOn();
  delay(d);

  redLED.turnOn();
  delay(d);

  greenLED.turnOff();
  delay(d);

  yellowLED.turnOff();
  delay(d);

  redLED.turnOff();
  
}

void SwitchLEDLoopSound(float d)
{
  greenLED.turnOn();
  buzzer.setFrequency(300);
  buzzer.playWithDelay(d);

  yellowLED.turnOn();
  buzzer.setFrequency(600);
  buzzer.playWithDelay(d);

  redLED.turnOn();
  buzzer.setFrequency(900);
  buzzer.playWithDelay(d);

  greenLED.turnOff();
  buzzer.setFrequency(600);
  buzzer.playWithDelay(d);

  yellowLED.turnOff();
  buzzer.setFrequency(300);
  buzzer.playWithDelay(d);

  redLED.turnOff();
  buzzer.stop();
}
