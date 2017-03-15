
#include <math.h>
#include "ultrasonic.h"
#include "IMU.h"


extern Ultrasonic LeftUltra;
extern Ultrasonic RightUltra;
extern Ultrasonic FrontUltra;

extern IMU myIMU;

float MagToHeading(float mx, float my, float mz) {
  return atan2(my, mx);
}

// Take measurements from sensors and update the state variables
void Measure(StateVariables* svars) {

  myIMU.updateAccelData();
  myIMU.updateGyroData();
  myIMU.updateMagData();

  unsigned long t_last = svars->t[NUM_FILTER];
  for (int i = 1; i < NUM_FILTER; i++) {
    svars->t[i] = svars->t[i-1];
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

    // Discrete integration acceleration -> velocity
    svars->v[dim][0] += 
      (svars->a[dim][0] * (svars->t[0]-svars->t[1]) 
        - svars->a[dim][NUM_FILTER-1] * (svars->t[NUM_FILTER-1] - t_last))
      /(NUM_FILTER * 1e-6);
  }

  svars->curheading = MagToHeading(svars->m[0][0], 
                                   svars->m[1][0], 
                                   svars->m[2][0]);

  switch (svars->curstate) {
    case StartSt:
      svars->initheading = svars->curheading;
      break;
    case SrcForw:
      svars->leftdist = LeftUltra.getDistance();
      svars->leftdist = LeftUltra.getDistance();
      svars->leftdist = LeftUltra.getDistance();
      break;
  }

}