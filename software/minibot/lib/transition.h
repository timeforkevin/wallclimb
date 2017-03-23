#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"
#include <math.h>

#define STARTSTOPACC 0.7
#define GRAVITY 9.81
#define MINULTRA 15
#define EPS 40
#define RAMPDIST 150
#define ULTCOUNTS 10

typedef bool (*TransTestFunc)(const StateVariables*);

bool __false(const StateVariables* svars) { return false; }

bool ___true(const StateVariables* svars) { return true; }

bool moving_(const StateVariables* svars) {
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
  if(svars->countTopa > 10) {
      return true;
  } else {
      return false;
  }
}

bool upright(const StateVariables* svars) {
  if(svars->countDesca > 10) {
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
  if(svars->countUltLeft > ULTCOUNTS) {
    return true;
  } else {
    return false;
  }
}

bool foundR_(const StateVariables* svars) {
  if(svars->countUltRight > ULTCOUNTS) {
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

bool hitend_(const StateVariables* svars) {
  if (svars->ultFront < 20) {
    return true;
  } else {
    return false;
  }
}

bool timerUp(const StateVariables* svars) {
  if (svars->t[0] > svars->tartime) {
    return true;
  } else {
    return false;
  }
}

bool foundF_(const StateVariables* svars) {
  if (svars->ultFront < MINULTRA &&
      svars->countUltLeft < ULTCOUNTS/3) {
    return true;
  } else {
    return false;
  }
}

bool nFoundF(const StateVariables* svars) {
  return !foundF_(svars);
}

const TransTestFunc TransTests[NUM_STATES][NUM_STATES] =
{           /* StartSt  AprWall  TopWall  DesWall  AdjHead  CheckFo  SrcForw  Turn90L  Turn90R  Turn180  AprBase  ClimbB2 StopSta */
/* StartSt */{ __false, moving_, __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, __false },
/* AprWall */{ __false, __false, timerUp, __false, __false, __false, __false, __false, __false, __false, __false, __false, __false },
/* TopWall */{ __false, __false, __false, descend, __false, __false, __false, __false, __false, __false, __false, __false, __false },
/* DesWall */{ __false, __false, __false, __false, upright, __false, __false, __false, __false, __false, __false, __false, __false },
/* AdjHead NOT USED ******************************************************************************************************************/{ __false, __false, __false, __false, __false, __false, ___true, __false, __false, __false, __false, __false, __false },
/* CheckFo NOT USED ******************************************************************************************************************/{ __false, __false, __false, __false, __false, __false, nFoundF, __false, __false, __false, foundF_, __false, __false },
/* SrcForw */{ __false, __false, __false, __false, __false, __false, __false, foundL_, __false, __false, __false, foundF_, __false },
/* Turn90L */{ __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, ___true, __false, __false },
/* Turn90R */{ __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, ___true, __false, __false },
/* Turn180 NOT USED ******************************************************************************************************************/{ __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, ___true },
/* AprBase */{ __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, hitend_, timerUp },
/* ClimbB2 */{ __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, ___true },
/* StopSta */{ __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, __false, ___true }
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
