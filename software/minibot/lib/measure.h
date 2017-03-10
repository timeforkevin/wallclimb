
#include <math.h>
#include "ultrasonic.h"
#include "IMU.h"


extern Ultrasonic LeftUltra;
extern Ultrasonic RightUltra;
extern Ultrasonic FrontUltra;

extern IMU myIMU;

float MagToHeading(float mx, float my, float mz) {
  return atan2(mx, my);
}

// Take measurements from sensors and update the state variables
void Measure(StateVariables* svars) {
  myIMU.updateAccelData();
  myIMU.updateGyroData();
  myIMU.updateMagData();

  svars->heading = MagToHeading(myIMU.getmx(), myIMU.getmy(), myIMU.getmz());

  svars->leftdist = LeftUltra.getDistance();

}