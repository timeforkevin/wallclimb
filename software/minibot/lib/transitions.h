#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include "states.h"

typedef bool (*TransTestFunc)(const StateVariables*);

bool invalid(const StateVariables* statevars) { return false; }

bool uncond_(const StateVariables* statevars) { return true; }

TransTestFunc TransTests[NUM_STATES][NUM_STATES] = 
{           /* AprWall  AscWall  DesWall  SrcForw  AprBase */
/* AprWall */{ uncond_, invalid, invalid, invalid, invalid },
/* AscWall */{ invalid, uncond_, invalid, invalid, invalid },
/* DesWall */{ invalid, invalid, uncond_, invalid, invalid },
/* SrcForw */{ invalid, invalid, invalid, uncond_, invalid },
/* AprBase */{ invalid, invalid, invalid, invalid, uncond_ }
};

void Transition(StateVariables* statevars) {
  for (int i = 0; i < NUM_STATES; i++) {
    if (TransTests[statevars->currentstate][i](statevars)) {
      statevars->currentstate = i;
      break;
    }
  }
}

#endif