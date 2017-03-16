
#include <math.h>
#include "ultrasonic.h"
#include "IMU.h"


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
  for (int i = 1; i < NUM_FILTER; i++) {
    svars->t[i] = svars->t[i-1];
    svars->leftdist[i] = svars->leftdist[i-1];
    svars->frontdist[i] = svars->frontdist[i-1];
    svars->rightdist[i] = svars->rightdist[i-1];
  }
  svars->t[0] = micros();

  for (int dim = 0; dim < 3; dim++) {
    // TODO: implement as circular buffer
    for (int i = 1; i < NUM_FILTER; i++) {
      svars->a[dim][i] = svars->a[dim][i-1];
      svars->g[dim][i] = svars->g[dim][i-1];
      svars->m[dim][i] = svars->m[dim][i-1];
      svars->v[dim][i] = svars->v[dim][i-1];
    }
    svars->a[dim][0] = myIMU.a[dim];
    svars->g[dim][0] = myIMU.g[dim];
    svars->m[dim][0] = myIMU.m[dim];

    // // Discrete integration acceleration -> velocity
    // svars->v[dim][0] += 
    //   (svars->a[dim][0] * (svars->t[0]-svars->t[1]) 
    //     - svars->a[dim][NUM_FILTER-1] * (svars->t[NUM_FILTER-1] - t_last))
    //   /(NUM_FILTER * 1e6);
  }

  svars->curheading = MagToHeading(svars->m[0], 
                                   svars->m[1], 
                                   svars->m[2]);
  long leftdist;
  long frontdist;
  long rightdist;

  switch (svars->curstate) {
    case StartSt:
      svars->initheading = svars->curheading;
      break;
    case CheckFo:
    
    case SrcForw:
      leftdist = LeftUltra.getDistance();
      frontdist = FrontUltra.getDistance();
      rightdist = RightUltra.getDistance();
      svars->leftdist[0] = (leftdist) ? leftdist : svars->leftdist[1];
      svars->frontdist[0] = (frontdist) ? frontdist : svars->frontdist[1];
      svars->rightdist[0] = (rightdist) ? rightdist : svars->rightdist[1];
      break;
  }

}