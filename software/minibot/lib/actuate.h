#include "motor.h"
#include "LED.h"

extern VexMotor LeftMotor;
extern VexMotor RightMotor;

// const unsigned long StateColours[] = {
//   0xFF0000, // StartSt : Red
//   0x7F7F00, // AprWall : Yellow
//   0x00FF00, // TopWall : Green
//   0x007F7F, // DesWall : Cyan
//   0x0000FF, // AdjHead : Blue
//   0x7F007F, // SrcForw : Magenta
//   0xFF7F00, // Turn90L : Orange
//   0x7FFF00, // Turn90R : Yellow Green
//   0x00FF7F, // Turn180 : Green Blue
//   0x007FFF, // AprBase : Light Blue
//   0x7F00FF, // : Purple
//   0xFF007F, // : Red Pink
//   0xFFFFFF, // : White
//   0x000000  // : Black
// };

const unsigned long StateColours[] = {
  0xFF0000, //  : Red
  0xFFFF00, //  : Yellow
  0x00FF00, //  : Green
  0x00FFFF, //  : Cyan
  0x0000FF, //  : Blue
  0xFF00FF, //  : Magenta
  0xFFFF00, //  : Orange
  0x00FF00, //  : Yellow Green
  0x00FFFF, //  : Green Blue
  0x0000FF, //  : Light Blue
  0xFF00FF, // : Purple
  0x000000, // : Black
  0xFFFFFF, // : White
  0x000000  // : Black
};

void TurnHeading(float turnangle) {
  if (turnangle > 0) {
    RightMotor.VexMotorWrite(28);
    LeftMotor.VexMotorWrite(-28);
    delay(250*abs(turnangle));

  } else {
    RightMotor.VexMotorWrite(-28);
    LeftMotor.VexMotorWrite(28);
    delay(450*abs(turnangle));
  }

  RightMotor.VexMotorWrite(0);
  LeftMotor.VexMotorWrite(0);
}


void DriveForwardSlow() {
  RightMotor.VexMotorWrite(25);
  LeftMotor.VexMotorWrite(40);
}

void StopDrive() {
  RightMotor.VexMotorWrite(0);
  LeftMotor.VexMotorWrite(0);
}

void DriveForward() {
  RightMotor.VexMotorWrite(58);
  // Delayed start for Left Motor
  delay(15);
  LeftMotor.VexMotorWrite(100);
}

void Actuate(StateVariables* svars) {
  // Update colour to represent state
  writeLEDColour(StateColours[svars->curstate]);
  switch (svars->curstate) {
    case StartSt:
      break;
    case AprWall:
      if (svars->transition) {
        svars->tartime = svars->t[0] + 6*1e6;
      }
      break;
    case TopWall:
      // Full speed ahead over the wall
      DriveForward();
      break;

    case DesWall:
      // Full speed ahead down the wall
      DriveForward();
      break;

    case AdjHead:
    case CheckFo:
      break;

    case SrcForw:
      // Drive straight
      if (svars->countUltLeft > 2) {
        StopDrive();
      } else {
        DriveForward();
      }
      break;

    case Turn90L:
      // Turn 90 degrees to left
      TurnHeading(M_PI/2);
      break;

    case Turn90R:
      // Turn 90 degrees to right
      TurnHeading(-M_PI/2);
      break;

    case Turn180:
      // Turn 180 degrees
      TurnHeading(M_PI);
      break;

    case AprBase:
      // Drive straight
      if (svars->transition) {
        svars->tartime = svars->t[0] + 5*1e6;
      }
      DriveForward();
    break;

    case ClimbB2:
      RightMotor.VexMotorWrite(20); // CHANGE THIS IF IT'S TURNING TOO MUCH AT THE END!!!
      LeftMotor.VexMotorWrite(100);
      delay(1000);
      RightMotor.VexMotorWrite(100); // CHANGE THIS IF IT'S TURNING TOO MUCH AT THE END!!!
      LeftMotor.VexMotorWrite(100);
      delay(500);
    break;

    case StopSta:
      RightMotor.VexMotorWrite(0);
      LeftMotor.VexMotorWrite(0);
    break;
  }
}
