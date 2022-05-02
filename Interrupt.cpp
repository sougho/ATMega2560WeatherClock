#include <Arduino.h>

bool intFired;

void oneSecondISR() {
  intFired = true;  
}
