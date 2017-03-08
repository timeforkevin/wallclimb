#define MINIBOT
#include "lib/states.h"
#include "lib/transitions.h"
#include "lib/motors.h"
#include "lib/LED.h"

StateVariables statevars;

VexMotor LeftMotor(LEFTREVERSED);
VexMotor RightMotor(RIGHTREVERSED);

void setup() {
  // put your setup code here, to run once:
  initLED();
}

void loop() {
  // put your main code here, to run repeatedly:

}
