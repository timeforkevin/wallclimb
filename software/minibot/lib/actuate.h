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
  0xFF0000, // StartSt : Red
  0xFFFF00, // AprWall : Yellow
  0x00FF00, // TopWall : Green
  0x00FFFF, // DesWall : Cyan
  0x0000FF, // AdjHead : Blue
  0xFF00FF, // SrcForw : Magenta
  0xFFFF00, // Turn90L : Orange
  0xFFFF00, // Turn90R : Yellow Green
  0x00FFFF, // Turn180 : Green Blue
  0x00FFFF, // AprBase : Light Blue
  0xFF00FF, // : Purple
  0xFF007F, // : Red Pink
  0xFFFFFF, // : White
  0x000000  // : Black
};

// Do we need Integral Control?
float err_int;
float controller(float err, unsigned long dt) {
  float Kp = 0.20*SPEED_MAX/M_PI;
  float Ki = 0;
  err_int += err*dt*1e-6;
Serial.print("err_int: ");
Serial.print(err_int);
  return Kp*err + Ki*err_int;
}

void TurnHeading(const StateVariables* svars) {
  float err = diffheading(svars->curheading, svars->tarheading);
  float u = controller(err, svars->t[0] - svars->t[1]);

  // if (u > 0.1*SPEED_MAX) {
  //   u = 0.1*SPEED_MAX;
  // } else if (u < -0.1*SPEED_MAX) {
  //   u = -0.1*SPEED_MAX;
  // }

  RightMotor.VexMotorWrite(u);
  LeftMotor.VexMotorWrite(-u);
Serial.print(" TURN");
Serial.print(" RightMotor:");
Serial.print(u);
Serial.print(" LeftMotor:");
Serial.print(-u);
}

void DriveForward(const StateVariables* svars) {
  float err = diffheading(svars->curheading, svars->tarheading);
  float u = controller(err, svars->t[0] - svars->t[1]);

  if (u > 0) {
    RightMotor.VexMotorWrite(SPEED_MAX);
    LeftMotor.VexMotorWrite(SPEED_MAX - 2*u);
Serial.print(" DRIVE");
Serial.print(" RightMotor:");
Serial.print(SPEED_MAX);
Serial.print(" LeftMotor:");
Serial.print(SPEED_MAX - 2*u);
  } else {
    RightMotor.VexMotorWrite(SPEED_MAX + 2*u);
    LeftMotor.VexMotorWrite(SPEED_MAX);
Serial.print(" RightMotor:");
Serial.print(SPEED_MAX + 2*u);
Serial.print(" LeftMotor:");
Serial.print(SPEED_MAX);
  }
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
        err_int = 0;
        svars->tarheading = svars->initheading;
      }
      TurnHeading(svars);
      break;

    case SrcForw:
      // Drive straight
      if (svars->transition) {
        err_int = 0;
      }
      DriveForward(svars);
      break;

    case Turn90L:
      // Turn 90 degrees to left
      if (svars->transition) {
        err_int = 0;
        svars->tarheading = svars->tarheading + M_PI/2;
        if (svars->tarheading > M_PI) {
          svars->tarheading -= 2*M_PI;
        }
      }
      TurnHeading(svars);
      break;

    case Turn90R:
      // Turn 90 degrees to right
      if (svars->transition) {
        err_int = 0;
        svars->tarheading = svars->tarheading - M_PI/2;
        if (svars->tarheading < -M_PI) {
          svars->tarheading += 2*M_PI;
        }
      }
      TurnHeading(svars);
      break;

    case Turn180:
      // Turn 180 degrees
      if (svars->transition) {
        err_int = 0;
        svars->tarheading = svars->tarheading + M_PI;
        if (svars->tarheading > M_PI) {
          svars->tarheading -= 2*M_PI;
        }
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