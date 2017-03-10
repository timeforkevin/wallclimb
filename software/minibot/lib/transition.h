#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"
#include <math.h>

typedef bool (*TransTestFunc)(const StateVariables*);

bool invalid(const StateVariables* svars) { return false; }

bool uncond_(const StateVariables* svars) { return true; }

bool foundb2(const StateVariables* svars) {
  if (svars->leftdist < 200) {
    return true;
  } else {
    return false;
  }
}

bool facingb(const StateVariables* svars) {
  if (abs(svars->heading 
          - (svars->initheading + M_PI/2)) < M_PI/12) {
    return true;
  } else {
    return false;
  }
}

TransTestFunc TransTests[NUM_STATES][NUM_STATES] = 
{           /* AprWall  AscWall  DesWall  SrcForw  Turn90d  AprBase */
/* AprWall */{ invalid, uncond_, invalid, invalid, invalid, invalid },
/* AscWall */{ invalid, invalid, uncond_, invalid, invalid, invalid },
/* DesWall */{ invalid, invalid, invalid, uncond_, invalid, invalid },
/* SrcForw */{ invalid, invalid, invalid, invalid, foundb2, invalid },
/* Turn90d */{ invalid, invalid, invalid, invalid, invalid, facingb },
/* AprBase */{ invalid, invalid, invalid, invalid, invalid, uncond_ }
};

// Tests each transition condition and makes the neccessary transition
void Transition(StateVariables* svars) {
  for (int i = 0; i < NUM_STATES; i++) {
    if (TransTests[svars->curstate][i](svars)) {
      svars->curstate = i;
      break;
    }
  }
}

#endif