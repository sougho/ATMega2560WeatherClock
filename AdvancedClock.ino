#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>


#include "DisplayUtils.h"
#include "Time.h"
#include "BMPUtils.h"
#include "PinDefs.h"
#include "EEPROM.h"
#include "Modes.h"
#include "ModeHandlers.h"
#include "MainPage.h"
#include "LargeFormatTime.h"


void handleSwitchValueRead(short val, short switchId);
void displayClockInitPage();
void createLayout(void);
void displayInit();
void initTransitionTable();

extern boolean intFired;
extern BMPUtils bmpManager;
extern DS3231 _s_clk;
extern short currentMode;

void oneSecondISR();

// Display page functions
typedef void (*DISPLAY_FUNCTION_TYPE) (void);

#define TOTALMODES 6

ModeHandler* functionalModes[NUM_STATES];

int currentDisplayedPage = 0;

EEPROM eeprom;


void setup() {
  
  Serial.begin(57600);

  Wire.begin();
  bmpManager.initBMP();

//  setToCompileTime();
//  delay(100);
 
  displayInit();
  createLayout();
  displayClockInitPage();

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), oneSecondISR, FALLING);

  _s_clk.enableOscillator(true, false, 0);

  functionalModes[0] = new MainPage();
  functionalModes[1] = new LargeFormatTime();
  initTransitionTable();
  
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
    if (currentMode < NUM_STATES)
      functionalModes[currentMode]->handleEvent(RENDER);
    else
      functionalModes[0]->handleEvent(RENDER);
    intFired = false;
  }
  int val = digitalRead(SWITCH_1_PIN);
  handleSwitchValueRead(val, 1);

  val = digitalRead(SWITCH_2_PIN);
  handleSwitchValueRead(val, 2);
 
  val = digitalRead(SWITCH_3_PIN);
  handleSwitchValueRead(val, 3);
}
