#define LIFTBOT
#include "lib/motor.h"

VexMotor LeftMotor(LEFTMOTORPIN, LEFTREVERSED, 1);
VexMotor RightMotor(RIGHTMOTORPIN, RIGHTREVERSED, 1);
VexMotor LiftMotor(LIFTMOTORPIN, LIFTREVERSED, 1);
VexMotor WinchMotor(WINCHMOTORPIN, WINCHREVERSED, 1);


void setup() {
  Serial.begin(9600);
  WinchMotor.init();
  LeftMotor.init();
  RightMotor.init();
  LiftMotor.init();

  //Drive off starting patform
  LeftMotor.VexMotorWrite(100);
  RightMotor.VexMotorWrite(100);
  LiftMotor.VexMotorWrite(100);
  delay(1500);
  
  //Turn left
  RightMotor.VexMotorWrite(30);
  delay(1500);
  
  //Turn right
  RightMotor.VexMotorWrite(100);
  LeftMotor.VexMotorWrite(25);
  delay(1500);

  //Approach wall
  LeftMotor.VexMotorWrite(1000);
  delay(1200);

  //Press against wall
  LiftMotor.VexMotorWrite(50);
  RightMotor.VexMotorWrite(50);
  LeftMotor.VexMotorWrite(50);

  //Drive winch, drop minibot
  WinchMotor.VexMotorWrite(100);
  delay(350);

  //Stop
  RightMotor.VexMotorWrite(0);
  LeftMotor.VexMotorWrite(0);
  LiftMotor.VexMotorWrite(0);

  //7.05 seconds to get to the wall
  delay(7000);

  //at the bottom, stop winch
  WinchMotor.VexMotorWrite(0);

}

void loop() {}
