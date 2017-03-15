#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"
#include <math.h>

#define GRAVITY 9.81
#define MAXULTRA 200
#define MINULTRA 15
#define EPS 100

typedef bool (*TransTestFunc)(const StateVariables*);

bool __false(const StateVariables* svars) { return false; }

bool ___true(const StateVariables* svars) { return true; }

bool moving_(const StateVariables* svars) {
  // TODO Define as constant
  if (abs(svars->v[0][0]) > 0.5 ||
      abs(svars->v[1][0]) > 0.5) {
    return true;
  } else {
    return false;
  }
}

bool nmoving(const StateVariables* svars) {
  return !moving_(svars);
}

bool descend(const StateVariables* svars) {
  // Facing downwards
  if (abs(svars->a[3][0]) < GRAVITY * 0.1) {
    return true;
  } else {
    return false;
  }
}

bool upright(const StateVariables* svars) {
  if (abs(svars->a[3][0]) > GRAVITY * 0.9) {
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
  if (svars->leftdist < MAXULTRA) {
    return true;
  } else {
    return false;
  }
}

bool foundR_(const StateVariables* svars) {
  if (svars->rightdist < MAXULTRA) {
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
  if (svars->frontdist < MINULTRA) {
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