#ifndef STATE_H
#define STATE_H

#define NUM_STATES 6
typedef enum {
  AprWall = 0,
  AscWall = 1,
  DesWall = 2,
  SrcForw = 3,
  Turn90d = 4,
  AprBase = 5
} State;

typedef struct {
  State curstate;
  unsigned long time;
  float heading;
  float x;
  float y;
  long leftdist;

  float initheading;
} StateVariables;

#endif