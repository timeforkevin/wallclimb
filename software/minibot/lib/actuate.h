#include "motor.h"

extern VexMotor LeftMotor;
extern VexMotor RightMotor;

void Actuate(const StateVariables* svars) {
  switch (svars->curstate) {
    case AprWall:
    case AscWall:
    case DesWall:
      break;
    case SrcForw:
      // Straight Forward
      LeftMotor.VexMotorWrite(100);
      RightMotor.VexMotorWrite(100);
      break;
    case Turn90d:
      // Turn Left
      LeftMotor.VexMotorWrite(-40);
      RightMotor.VexMotorWrite(40);
      break;
    case AprBase:
      // Straight Forward
      LeftMotor.VexMotorWrite(100);
      RightMotor.VexMotorWrite(100);
      break;
  }
}