#include "motor.h"
#include "LED.h"

extern VexMotor LeftMotor;
extern VexMotor RightMotor;

const unsigned long StateColours[] = {
  0xFF0000,
  0x7F7F00,
  0x00FF00,
  0x007F7F,
  0x0000FF,
  0x7F007F,
  0xFF7F00,
  0x7FFF00,
  0x00FF7F,
  0x007FFF,
  0x7F00FF,
  0xFFFFFF,
  0x000000
};

void Actuate(const StateVariables* svars) {
  switch (svars->curstate) {
    // case SrcForw:
    //   // Straight Forward
    //   LeftMotor.VexMotorWrite(100);
    //   RightMotor.VexMotorWrite(100);
    //   break;
    // case Turn90d:
    //   // Turn Left
    //   LeftMotor.VexMotorWrite(-40);
    //   RightMotor.VexMotorWrite(40);
    //   break;
    // case AprBase:
    //   // Straight Forward
    //   LeftMotor.VexMotorWrite(100);
    //   RightMotor.VexMotorWrite(100);
    //   break;
  }
  writeLEDColour(StateColours[svars->curstate]);
}