#define MINIBOT
#include "lib/state.h"
#include "lib/transition.h"
#include "lib/measure.h"
#include "lib/actuate.h"
#include "lib/motor.h"
#include "lib/LED.h"
#include "lib/ultrasonic.h"
#include "lib/IMU.h"

StateVariables statevars;

VexMotor LeftMotor(LEFTMOTORPIN, LEFTREVERSED);
VexMotor RightMotor(RIGHTMOTORPIN, RIGHTREVERSED);

Ultrasonic LeftUltra(LEFTECHOPIN, LEFTTRIGPIN);
Ultrasonic RightUltra(RIGHTECHOPIN, RIGHTTRIGPIN);
Ultrasonic FrontUltra(FRONTECHOPIN, FRONTTRIGPIN);

IMU myIMU;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  initLED();
  myIMU.init();
  LeftMotor.init();
  RightMotor.init();

  LeftUltra.init();
  RightUltra.init();
  FrontUltra.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Measure(&statevars);
  Transition(&statevars);
  Actuate(&statevars);
}
