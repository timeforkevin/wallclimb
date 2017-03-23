
#include <math.h>
#include "ultrasonic.h"
#include "IMU.h"

#define GRAVITY 9.81
#define ZAXIS 1

extern Ultrasonic LeftUltra;
extern Ultrasonic RightUltra;
extern Ultrasonic FrontUltra;

extern IMU myIMU;

float MagToHeading(float* mx, float* my, float* mz) {
  float sumx = 0;
  float sumy = 0;
  float sumz = 0;
  for (int i = 0; i < NUM_FILTER; i++) {
    sumx += mx[i];
    sumy += my[i];
    sumz += mz[i];
  }
  return atan2(sumy, sumx);
}

// Take measurements from sensors and update the state variables
void Measure(StateVariables* svars) {

  myIMU.updateAccelData();
  myIMU.updateGyroData();
  myIMU.updateMagData();

  unsigned long t_last = svars->t[NUM_FILTER];
  svars->t[0] = micros();

  for (int dim = 0; dim < 3; dim++) {
    // TODO: implement as circular buffer
    for (int i = 1; i < NUM_FILTER; i++) {
      svars->a[dim][i] = svars->a[dim][i-1];
      svars->g[dim][i] = svars->g[dim][i-1];
    }
    svars->a[dim][0] = myIMU.a[dim];
    svars->g[dim][0] = myIMU.g[dim];
  }

  int leftdist;
  int frontdist;
  int rightdist;

  switch (svars->curstate) {
    case StartSt:
      svars->initheading = svars->curheading;
      break;

    case CheckFo:
    case AprBase:
      // Delay for eliminating ultrasonic crosstalk
      delay(7);
      frontdist = FrontUltra.getDistance();
      svars->ultFront = (frontdist) ? frontdist : svars->ultFront;
      break;

    case SrcForw:
      // Delay for eliminating ultrasonic crosstalk
      delay(7);
      leftdist = LeftUltra.getDistance();
      delay(7);
      frontdist = FrontUltra.getDistance();
      delay(7);
      rightdist = RightUltra.getDistance();
      svars->newUltLeft = (leftdist) ? leftdist : svars->newUltLeft;
      svars->ultFront = (frontdist) ? frontdist : svars->ultFront;
      svars->newUltRight = (rightdist) ? rightdist : svars->newUltRight;

      if(svars->oldUltLeft - svars->newUltLeft > 20) {
        svars->countUltLeft += 1;
      }
      else if (abs(svars->newUltLeft - svars->oldUltLeft) < 20) {
        if(svars->countUltLeft>0) {
          svars->countUltLeft -= 1;
        }
        svars->oldUltLeft = svars->newUltLeft;
      }
      if(svars->oldUltRight - svars->newUltRight > 20) {
        svars->countUltRight += 1;
      }
      else if (abs(svars->newUltRight - svars->oldUltRight) < 20) {
        if(svars->countUltRight>0) {
          svars->countUltRight -= 1;
        }
        svars->oldUltRight = svars->newUltRight;
      }

    break;

    case TopWall:
      if(svars->a[ZAXIS][NUM_FILTER] < 0.2*GRAVITY ) {
          svars->countTopa += 1;
      }
      else {
          if(svars->countTopa>0) {
              svars->countTopa -= 1;
          }
      }
    break;

    case DesWall:
      if(svars->a[ZAXIS][NUM_FILTER] > 0.8*GRAVITY ) {
          svars->countDesca += 1;
      }
      else {
          if(svars->countDesca>0) {
              svars->countDesca -= 1;
          }
      }
    break;

    }

}
