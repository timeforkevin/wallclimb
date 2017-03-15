#include "motor.h"
#include "LED.h"

extern VexMotor LeftMotor;
extern VexMotor RightMotor;

const unsigned long StateColours[] = {
  0xFF0000, // StartSt : Red
  0x7F7F00, // AprWall : Yellow
  0x00FF00, // TopWall : Green
  0x007F7F, // DesWall : Cyan
  0x0000FF, // AdjHead : Blue
  0x7F007F, // SrcForw : Magenta
  0xFF7F00, // Turn90L : Orange
  0x7FFF00, // Turn90R : Yellow Green
  0x00FF7F, // Turn180 : Green Blue
  0x007FFF, // AprBase : Light Blue
  0x7F00FF, // : Purple
  0xFF007F, // : Red Pink
  0xFFFFFF, // : White
  0x000000  // : Black
};

// Do we need Integral Control?
float controller(float err) {
  float Kp_turn = SPEED_MAX/M_PI;
  return Kp_turn*err;
}

void TurnHeading(const StateVariables* svars) {
  float err = diffheading(svars->curheading, svars->tarheading);
  float u = controller(err);

  RightMotor.VexMotorWrite(u);
  LeftMotor.VexMotorWrite(-u);
}

void DriveForward(const StateVariables* svars) {
  float err = diffheading(svars->curheading, svars->tarheading);
  float u = controller(err);

  RightMotor.VexMotorWrite(SPEED_MAX);
  LeftMotor.VexMotorWrite(SPEED_MAX - 2*u);
}

void Actuate(StateVariables* svars) {
  switch (svars->curstate) {
    case StartSt:
    case AprWall:
    case TopWall:
      // Do Nothing
      break;

    case DesWall:
      // Full speed ahead down the wall
      RightMotor.VexMotorWrite(SPEED_MAX);
      LeftMotor.VexMotorWrite(SPEED_MAX);
      break;

    case AdjHead:
      // Turn to face forward
      if (svars->transition) {
        svars->tarheading = svars->initheading;
      }
      TurnHeading(svars);
      break;

    case SrcForw:
      // Drive straight
      DriveForward(svars);
      break;

    case Turn90L:
      // Turn 90 degrees to left
      if (svars->transition) {
        svars->tarheading = svars->tarheading + M_PI/2;
      }
      TurnHeading(svars);
      break;

    case Turn90R:
      // Turn 90 degrees to right
      if (svars->transition) {
        svars->tarheading = svars->tarheading - M_PI/2;
      }
      TurnHeading(svars);
      break;

    case Turn180:
      // Turn 180 degrees
      if (svars->transition) {
        svars->tarheading = svars->tarheading + M_PI;
      }
      TurnHeading(svars);
      break;

    case AprBase:
      // Drive straight
      DriveForward(svars);
      break;
  }
  // Update colour to represent state
  writeLEDColour(StateColours[svars->curstate]);
}