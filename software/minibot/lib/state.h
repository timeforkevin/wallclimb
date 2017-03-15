#ifndef STATE_H
#define STATE_H

#include <math.h>

#define NUM_FILTER 4

#define NUM_STATES 10
typedef enum {
  StartSt = 0,
  AprWall = 1,
  TopWall = 2,
  DesWall = 3,
  AdjHead = 4,
  SrcForw = 5,
  Turn90L = 6,
  Turn90R = 7,
  Turn180 = 8,
  AprBase = 9
} State;

typedef struct {
  float initheading;
  float curheading;
  float tarheading;

  float a[3][NUM_FILTER];
  float g[3][NUM_FILTER];
  float m[3][NUM_FILTER];
  float v[3][NUM_FILTER];

  unsigned long t[NUM_FILTER];

  long leftdist;
  long frontdist;
  long rightdist;

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