#define LIFTBOT
// #include "lib/state.h"
// #include "lib/transition.h"
// #include "lib/measure.h"
// #include "lib/actuate.h"
#include "lib/motor.h"
// #include "lib/LED.h"
// #include "lib/ultrasonic.h"
// #include "lib/IMU.h"

VexMotor LeftMotor(LEFTMOTORPIN, LEFTREVERSED);
VexMotor RightMotor(RIGHTMOTORPIN, RIGHTREVERSED);
VexMotor LiftMotor(LIFTMOTORPIN, LIFTREVERSED);
VexMotor WinchMotor(WINCHMOTORPIN, WINCHREVERSED);


void setup() {
  Serial.begin(9600);
  WinchMotor.init();
  LeftMotor.init();
  RightMotor.init();
  LiftMotor.init();

  //start with turn
  LeftMotor.VexMotorWrite(100);
  RightMotor.VexMotorWrite(100);
  LiftMotor.VexMotorWrite(100);

  delay(1500);
  
  RightMotor.VexMotorWrite(30);
  delay(1500);
  
  RightMotor.VexMotorWrite(100);
  LeftMotor.VexMotorWrite(25);

  delay(1500);

  //go straight
  LeftMotor.VexMotorWrite(1000);

  delay(1200);

  RightMotor.VexMotorWrite(0);
  LeftMotor.VexMotorWrite(0);

  delay(1000);

    //once at the top, start winch

  LiftMotor.VexMotorWrite(10);
  RightMotor.VexMotorWrite(50);
  LeftMotor.VexMotorWrite(50);
  //WinchMotor.VexMotorWrite(100); // +ve

  delay(350);
  RightMotor.VexMotorWrite(0);
  LeftMotor.VexMotorWrite(0);
  LiftMotor.VexMotorWrite(0);

// 7.05 seconds to get to the wall
   delay(7000);

  //at the bottom, stop winch
  WinchMotor.VexMotorWrite(0);

}

void loop() {
	// i don't think we need anything here
}
