#ifndef STATE_H
#define STATE_H

#define NUM_STATES 5
typedef enum {
  AprWall = 0,
  AscWall = 1,
  DesWall = 2,
  SrcForw = 3,
  AprBase = 4
} State;

typedef struct {
  State currentstate;
  unsigned long time;
  float heading;
  float x;
  float y;
} StateVariables;

#endif