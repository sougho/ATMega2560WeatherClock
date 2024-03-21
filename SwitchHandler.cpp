#include <Arduino.h>

short swPressDuration[3];

void handleSwitchValueRead(short val, short switchId) {
  if (val == 0) {
    delay(200);
    swPressDuration[switchId-1] ++;
  } else {
    if ((swPressDuration[switchId-1] > 0) &&(swPressDuration[switchId-1] <= 3)){
      Serial.print("SW Short Pressed: " + String(switchId));
    } else if (swPressDuration[switchId-1] > 0){
      Serial.print("SW Long Pressed: " + String(switchId));
    }
    swPressDuration[switchId-1] = 0;
  }
}
