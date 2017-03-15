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
  LeftMotor.VexMotorWrite(50);
  RightMotor.VexMotorWrite(40);
  LiftMotor.VexMotorWrite(50);

  delay(500);

  //go straight
  RightMotor.VexMotorWrite(50);

  delay(500);

  //once at the top, start winch
  RightMotor.VexMotorWrite(0);
  LeftMotor.VexMotorWrite(0);
  LiftMotor.VexMotorWrite(0);
  WinchMotor.VexMotorWrite(50);

  //at the bottom, stop winch
  WinchMotor.VexMotorWrite(0);

}

void loop() {
	// i don't think we need anything here
}
