#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"
#include <math.h>

#define STARTSTOPACC 0.7
#define GRAVITY 9.81
#define ULTRATHRESH 10
#define MINULTRA 15
#define EPS 40

typedef bool (*TransTestFunc)(const StateVariables*);

bool __false(const StateVariables* svars) { return false; }

bool ___true(const StateVariables* svars) { return true; }

bool moving_(const StateVariables* svars) {
  // // TODO Define as constant
  // if (abs(svars->v[0][0]) > 0.5 ||
  //     abs(svars->v[1][0]) > 0.5) {
  //   return true;
  // } else {
  //   return false;
  // }
  float avg = 0;
  for (int i = 0; i < NUM_FILTER; i++) {
    avg += svars->a[0][i];
  }
  avg /= NUM_FILTER;

  if (avg > STARTSTOPACC) {
    return true;
  } else {
    return false;
  }
}

bool nmoving(const StateVariables* svars) {
  float avg = 0;
  for (int i = 0; i < NUM_FILTER; i++) {
    avg += svars->a[0][i];
  }
  avg /= NUM_FILTER;

  if (avg < -STARTSTOPACC) {
    return true;
  } else {
    return false;
  }
}

bool descend(const StateVariables* svars) {
  // Facing downwards
  float avg = 0;
  for (int i = 0; i < NUM_FILTER; i++) {
    avg += svars->a[2][i];
  }
  avg /= NUM_FILTER;
  if (abs(avg) < GRAVITY * 0.1) {
    return true;
  } else {
    return false;
  }
}

bool upright(const StateVariables* svars) {
  float avg = 0;
  for (int i = 0; i < NUM_FILTER; i++) {
    avg += svars->a[2][i];
  }
  avg /= NUM_FILTER;
  if (abs(avg) > GRAVITY * 0.9) {
    return true;
  } else {
    return false;
  }
}

bool facefor(const StateVariables* svars) {
  if (abs(diffheading(svars->curheading, 
                      svars->initheading)) < 2*M_PI/EPS) {
    return true;
  } else {
    return false;
  }
}

bool foundL_(const StateVariables* svars) {
  int avg = 0;
  for (int i = 1; i < NUM_FILTER; i++) {
    avg += svars->leftdist[i];
  }
  avg /= (NUM_FILTER-1);

  if (abs(svars->leftdist[0] - avg) > ULTRATHRESH) {
    return true;
  } else {
    return false;
  }
}

bool foundR_(const StateVariables* svars) {
  int avg = 0;
  for (int i = 1; i < NUM_FILTER; i++) {
    avg += svars->rightdist[i];
  }
  avg /= (NUM_FILTER-1);

  if (abs(svars->rightdist[0] - avg) > ULTRATHRESH) {
    return true;
  } else {
    return false;
  }
}

bool facetar(const StateVariables* svars) {
  if (abs(diffheading(svars->curheading, 
                      svars->tarheading)) < 2*M_PI/EPS) {
    return true;
  } else {
    return false;
  }
}

bool hitback(const StateVariables* svars) {
  if (svars->frontdist[0] < MINULTRA) {
    return true;
  } else {
    return false;
  }
}

const TransTestFunc TransTests[NUM_STATES][NUM_STATES] = 
{           /* StartSt  AprWall  TopWall  DesWall  AdjHead  SrcForw  Turn90L  Turn90R  Turn180  AprBase */
/* StartSt */{ __false, moving_, __false, __false, __false, __false, __false, __false, __false, __false },
/* AprWall */{ __false, __false, nmoving, __false, __false, __false, __false, __false, __false, __false },
/* TopWall */{ __false, __false, __false, descend, __false, __false, __false, __false, __false, __false },
/* DesWall */{ __false, __false, __false, __false, upright, __false, __false, __false, __false, __false },
/* AdjHead */{ __false, __false, __false, __false, __false, facefor, __false, __false, __false, __false },
/* SrcForw */{ __false, __false, __false, __false, __false, __false, foundL_, foundR_, hitback, __false },
/* Turn90L */{ __false, __false, __false, __false, __false, __false, __false, __false, __false, facetar },
/* Turn90R */{ __false, __false, __false, __false, __false, __false, __false, __false, __false, facetar },
/* Turn180 */{ __false, __false, __false, __false, __false, facetar, __false, __false, __false, __false },
/* AprBase */{ __false, __false, __false, __false, __false, __false, __false, __false, __false, ___true }
};

// Tests each transition condition and makes the neccessary transition
void Transition(StateVariables* svars) {
  svars->transition = false;
  for (int i = 0; i < NUM_STATES; i++) {
    if (TransTests[svars->curstate][i](svars)) {
      svars->curstate = i;
      svars->transition = true;
      break;
    }
  }
}

#endif