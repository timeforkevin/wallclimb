#ifndef STATE_H
#define STATE_H

#include <math.h>

#define NUM_FILTER 4

#define NUM_STATES 13
typedef enum {
  StartSt = 0,
  AprWall = 1,
  TopWall = 2,
  DesWall = 3,
  AdjHead = 4,
  CheckFo = 5,
  SrcForw = 6,
  Turn90L = 7,
  Turn90R = 8,
  Turn180 = 9,
  AprBase = 10,
  ClimbB2 = 11,
  StopSta = 12
} State;

typedef struct {
  float initheading;
  float curheading;
  float tarheading;

  int countTopa;
  int countDesca;

  float a[3][NUM_FILTER];
  float g[3][NUM_FILTER];

  unsigned long t[NUM_FILTER];
  unsigned long tartime;

  int oldUltLeft;
  int newUltLeft;
  int countUltLeft;
  int oldUltRight;
  int newUltRight;
  int countUltRight;
  int ultFront;

  State curstate;
  bool transition;
} StateVariables;

float diffheading(float h1, float h2) {
  float diff = h2 - h1;
  if (diff > M_PI) {
    diff = -(2*M_PI - diff);
  } else if (diff < -M_PI) {
    diff = 2*M_PI + diff;
  }
  return diff;
}

#endif
