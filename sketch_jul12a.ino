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
}
