#include "Button.h"
#include "LEDLight.h"
#include "Buzzer.h"
#include "Bomb.h"
#include "GameManager.h"

// PHYSICAL COMPONENTS

Button btnA = Button(9);
Button btnB = Button(10);
Button btnC = Button(11);

LEDLight greenLED = LEDLight(4);
LEDLight yellowLED = LEDLight(5);
LEDLight redLED = LEDLight(6);

Buzzer buzzer = Buzzer(13, 300);

// COMPLEX OJBECTS

Bomb bomb = Bomb(buzzer, redLED, yellowLED, greenLED);

GameManager gm = GameManager(bomb, btnA, btnB, btnC);

void setup() {

  // SET PIN MODES
  
  btnA.setPinMode();
  btnB.setPinMode();
  btnC.setPinMode();

  greenLED.setPinMode();
  yellowLED.setPinMode();
  redLED.setPinMode();

  buzzer.setPinMode();

  // SETUP EFFECTS

  bomb.defuseEffect();

}

void loop() {
  gm.update();
}
