#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>
#include "DisplayUtils.h"
#include "Time.h"
#include "PinDefs.h"
#include "EEPROM.h"
#include "Modes.h"
#include "ModeHandlers.h"
#include "MainPage.h"
#include "LargeFormatTime.h"
#include "MemLocs.h"
#include "SensorData.h"


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

  delay(100);
  readSensors();
  displayInit();

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), oneSecondISR, FALLING);

  _s_clk.enableOscillator(true, false, 0);

  functionalModes[0] = new MainPage();
  functionalModes[1] = new LargeFormatTime();
  initTransitionTable();

  currentMode = EEPROM::readEEPROM(CURR_DISPLAY_PAGE);
  ModeHandler * currModeHandler = functionalModes[currentMode];
  currModeHandler->handleEvent(SW1_SHORT);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SWITCH_1_PIN, INPUT_PULLUP);
  pinMode(SWITCH_2_PIN, INPUT_PULLUP);
  pinMode(SWITCH_3_PIN, INPUT_PULLUP);

  digitalWrite(BUZZER_PIN, 1);
  delay(100);
  digitalWrite(BUZZER_PIN, 0);
}

long delayCounterFlash = 0;
#define FLASH_INTERVAL 10000L

// Sensor Read Event
#define SENSOR_READ_INTERVAL 300
int sensorIntervalCtr = 0;

void loop() {
  if (intFired) {
     intFired = false;
    if (currentMode < NUM_STATES)
      functionalModes[currentMode]->handleEvent(RENDER);
    else
      functionalModes[0]->handleEvent(RENDER);
    sensorIntervalCtr ++;
    if (sensorIntervalCtr == SENSOR_READ_INTERVAL) {
      sensorIntervalCtr = 0;
      readSensors();
    }
  }
  int val = digitalRead(SWITCH_1_PIN);
  handleSwitchValueRead(val, 1);

  val = digitalRead(SWITCH_2_PIN);
  handleSwitchValueRead(val, 2);
 
  val = digitalRead(SWITCH_3_PIN);
  handleSwitchValueRead(val, 3);

  // delayCounterFlash ++;
  // if (delayCounterFlash == 10000L) {
  //   functionalModes[currentMode]->handleEvent(FLASH);
  //   delayCounterFlash = 0;
  // }
}
