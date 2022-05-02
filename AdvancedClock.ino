#include <Arduino.h>
#include <Wire.h>

#include "BMPUtils.h"
#include "DHT22Utils.h"
#include "DisplayUtils.h"
#include "Time.h"

#include <DS3231.h>

long secCounter = 0;

#define DHTPIN_PRIMARY 14

BMPUtils bmpManager;
DHT22Utils dht22ManagerPrimary(DHTPIN_PRIMARY);

void setup() {

  Serial.begin(57600);
  
  DisplayUtils::init();
  DisplayUtils::createLayout();

  Wire.begin();
  bmpManager.initBMP();

  // setToCompileTime();
  // delay(100);
  
  AClkTime currTime = readCurrentTimeValue();
  DisplayUtils::printCalender(currTime.firstDayOfMonth, 31, currTime.day);
  DisplayUtils::printCurrentTime(currTime.hr24,currTime.mn, currTime.ss, true);

   printHumidity(92, 2);
   printPressure(92, 11);
}


void loop() {
  delay(1000);
  AClkTime currTime = readCurrentTimeValue();
  DisplayUtils::printCalender(currTime.firstDayOfMonth, 31, currTime.day);
  DisplayUtils::printCurrentTime(currTime.hr24,currTime.mn, currTime.ss, true);

  if (secCounter == 30) {
    printHumidity(92, 2);
    printPressure(92, 11);
    secCounter = 0;
  }

  if ((currTime.hr24 == 0) && (currTime.mn == 0) && ( currTime.ss <=2))
  {
    DisplayUtils::printCalender(currTime.firstDayOfMonth, 31, currTime.day);
  }
}

void printError(String s) {
  GLCD.CursorTo(15, 7);
  GLCD.print(s);
}


void printHumidity(int xOrigin, int yOrigin) {
 DHT22Data data = dht22ManagerPrimary.readRHValue();
 GLCD.CursorToXY(xOrigin, yOrigin);
 if (data.msg != NULL) {
   printError(data.msg);
 } else {
  GLCD.print("H:" + String(data.rh,0));
 }
}

void printPressure(int xOrigin, int yOrigin) {
  BMPData data = bmpManager.getPressureTempData();
  if (data.msg != NULL) {
    printError(data.msg);
  } else {
    GLCD.CursorToXY(xOrigin, yOrigin);
    GLCD.print("T:" + String(data.temp,0));
    GLCD.CursorToXY(xOrigin, yOrigin + 10);
    GLCD.print("P:" + String(data.pressure, 0));
  }
}

void printDuePoint(int xOrigin, int yOrigin) {
    GLCD.CursorToXY(xOrigin, yOrigin);
    GLCD.print("D:" + String(20.0,1));
}

void drawCurve (int points[], int length, int bottomLeftX, int bottomRightY) {
    for (int i = 0; i < length; i++) {
      
    }
}
