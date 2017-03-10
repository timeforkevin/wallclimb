#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"

typedef bool (*TransTestFunc)(const StateVariables*);

bool invalid(const StateVariables* statevars) { return false; }

bool uncond_(const StateVariables* statevars) { return true; }

TransTestFunc TransTests[NUM_STATES][NUM_STATES] = 
{           /* AprWall  AscWall  DesWall  SrcForw  AprBase */
/* AprWall */{ invalid, uncond_, invalid, invalid, invalid },
/* AscWall */{ invalid, invalid, uncond_, invalid, invalid },
/* DesWall */{ invalid, invalid, invalid, uncond_, invalid },
/* SrcForw */{ invalid, invalid, invalid, invalid, invalid },
/* AprBase */{ invalid, invalid, invalid, invalid, uncond_ }
};

// Tests each transition condition and makes the neccessary transition
void Transition(StateVariables* statevars) {
  for (int i = 0; i < NUM_STATES; i++) {
    if (TransTests[statevars->currentstate][i](statevars)) {
      statevars->currentstate = i;
      break;
    }
  }
}

bool foundb2(const StateVariables* statevars) {
  return true;
}

#endif