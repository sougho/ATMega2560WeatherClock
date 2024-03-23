
#include "Modes.h"

short transitionTable[NUM_STATES][NUM_EVENTS];

void initTransitionTable () {
  transitionTable[0][0] = 1;
  transitionTable[0][4] = 1;
  transitionTable[1][0] = 0;
  transitionTable[1][4] = 0;
}
