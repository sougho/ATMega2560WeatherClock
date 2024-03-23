#include <Arduino.h>
#include "Modes.h"
#include "ModeHandlers.h"

short swPressDuration[3];
short currentMode = 0;
extern short transitionTable[NUM_STATES][NUM_EVENTS];
extern ModeHandler* functionalModes[NUM_STATES];

void handleSwitchValueRead(short val, short switchId) {
  if (val == 0) {
    delay(200);
    swPressDuration[switchId-1] ++;
  } else {
    if ((swPressDuration[switchId-1] > 0) &&(swPressDuration[switchId-1] <= 3)){
      Serial.print("SW Short Pressed: " + String(switchId));
      // Handle switch short press
      short eventId = 2 * (switchId -1);
      Serial.print("EventId:" + String(eventId) + "Mode:" + String(currentMode));
      currentMode = transitionTable[currentMode][eventId];
      functionalModes[currentMode]->handleEvent(eventId);
    
    } else if (swPressDuration[switchId-1] > 0){
      Serial.print("SW Long Pressed: " + String(switchId));
    }
    swPressDuration[switchId-1] = 0;
  }
}
