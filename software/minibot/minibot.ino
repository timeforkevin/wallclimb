#define MINIBOT
#include "lib/state.h"
#include "lib/transition.h"
#include "lib/measure.h"
#include "lib/actuate.h"
#include "lib/motor.h"
#include "lib/LED.h"
#include "lib/ultrasonic.h"
#include "lib/IMU.h"

  StateVariables statevars = {0};

  VexMotor LeftMotor(LEFTMOTORPIN, LEFTREVERSED);
  VexMotor RightMotor(RIGHTMOTORPIN, RIGHTREVERSED);

  Ultrasonic RightUltra(RIGHTECHOPIN, RIGHTTRIGPIN);
  Ultrasonic LeftUltra(LEFTECHOPIN, LEFTTRIGPIN);
  Ultrasonic FrontUltra(FRONTECHOPIN, FRONTTRIGPIN);

  IMU myIMU;

#define BLINKDELAY 100

void blink(int seconds) {
  for (int i = 0; i < seconds; i++) {
    for (int j = 0; j < 500/BLINKDELAY; j++) {
      writeLEDColour(0x00FF7F);
      delay(BLINKDELAY);
      writeLEDColour(0x000000);
      delay(BLINKDELAY);
    }
  }
}

void printtransition() {
  if (statevars.transition) {
    Serial.print(statevars.curstate);
    LeftMotor.VexMotorWrite(0);
    RightMotor.VexMotorWrite(0);
    delay(1000);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  statevars.curstate = StartSt;
  statevars.v[0][0] = 0;
  statevars.v[1][0] = 0;
  statevars.v[2][0] = 0;

  // LED White during calibration
  initLED();
  writeLEDColour(0x00FF7F);
  
  myIMU.init();
  LeftMotor.init();
  RightMotor.init();

  LeftUltra.init();
  RightUltra.init();
  FrontUltra.init();

  blink(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  Measure(&statevars);
Serial.print(statevars.curstate);
Serial.print(" : ");
//Serial.print(" mx:");
//Serial.print(statevars.m[0][0]);
//Serial.print(" my:");
//Serial.print(statevars.m[1][0]);
//Serial.print(" mz:");
//Serial.print(statevars.m[2][0]);
Serial.print(" curh:");
Serial.print(statevars.curheading);
Serial.print(" tarh:");
Serial.print(statevars.tarheading);
  Transition(&statevars);
//printtransition();
  Actuate(&statevars);
Serial.print("\n");
}
