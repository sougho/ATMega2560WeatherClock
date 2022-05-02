#include <Arduino.h>
#include <Wire.h>


#include "DisplayUtils.h"
#include "Time.h"
#include "BMPUtils.h"

#include <DS3231.h>



extern boolean intFired;
extern BMPUtils bmpManager;
extern DS3231 _s_clk;

void oneSecondISR();

void setup() {

  Serial.begin(57600);

  DisplayUtils::init();
  DisplayUtils::createLayout();

  Wire.begin();
  bmpManager.initBMP();
  
  // setToCompileTime();
  // delay(100);

  DisplayUtils::displayClockInitPage();

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), oneSecondISR, FALLING);

  _s_clk.enableOscillator(true, false, 0);
}


void loop() {
  if (intFired) {
    DisplayUtils::displayClockPageOne();
    intFired = false;
  }
}
