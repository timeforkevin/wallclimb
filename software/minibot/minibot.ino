#define MINIBOT
#include "lib/states.h"
#include "lib/transitions.h"
#include "lib/motors.h"
#include "lib/LED.h"
#include "lib/ultrasonic.h"

StateVariables statevars;

VexMotor LeftMotor(LEFTMOTORPIN, LEFTREVERSED);
VexMotor RightMotor(RIGHTMOTORPIN, RIGHTREVERSED);

Ultrasonic LeftUltra(LEFTECHOPIN, LEFTTRIGPIN);
Ultrasonic RightUltra(RIGHTECHOPIN, RIGHTTRIGPIN);
Ultrasonic FrontUltra(FRONTECHOPIN, FRONTTRIGPIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  initLED();
  LeftMotor.init();
  RightMotor.init();

  LeftUltra.init();
  RightUltra.init();
  FrontUltra.init();
}

void loop() {
  // put your main code here, to run repeatedly:
}
