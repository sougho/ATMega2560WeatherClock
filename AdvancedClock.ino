#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>


#include "DisplayUtils.h"
#include "Time.h"
#include "BMPUtils.h"
#include "PinDefs.h"
#include "EEPROM.h"

void handleSwitchValueRead(short val, short switchId);

extern boolean intFired;
extern BMPUtils bmpManager;
extern DS3231 _s_clk;

void oneSecondISR();

// Display page functions
typedef void (*DISPLAY_FUNCTION_TYPE) (void);

#define TOTALMODES 6

DISPLAY_FUNCTION_TYPE functionalModes[TOTALMODES];

int currentDisplayedPage = 0;

EEPROM eeprom;


void setup() {
  
  Serial.begin(57600);

  DisplayUtils::init();
  //DisplayUtils::createLayout();

  Wire.begin();
  bmpManager.initBMP();

//  setToCompileTime();
//  delay(100);

 DisplayUtils::displayClockInitPage();

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), oneSecondISR, FALLING);

  _s_clk.enableOscillator(true, false, 0);

  functionalModes[0] = DisplayUtils::displayClockPageOne;
  functionalModes[1] = DisplayUtils::displayClockPageTwo;
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SWITCH_1_PIN, INPUT_PULLUP);
  pinMode(SWITCH_2_PIN, INPUT_PULLUP);
  pinMode(SWITCH_3_PIN, INPUT_PULLUP);

  digitalWrite(BUZZER_PIN, 1);
  delay(200);
  digitalWrite(BUZZER_PIN, 0);
}

void loop() {
  if (intFired) {
    if ( currentDisplayedPage < 4)
      functionalModes[currentDisplayedPage]();
    else
      functionalModes[0]();
    intFired = false;
  }
  int val = digitalRead(SWITCH_1_PIN);
  handleSwitchValueRead(val, 1);

  val = digitalRead(SWITCH_2_PIN);
  handleSwitchValueRead(val, 2);
 
  val = digitalRead(SWITCH_3_PIN);
  handleSwitchValueRead(val, 3);
}
