#include <Arduino.h>
#include <Wire.h>

#include "BMPUtils.h"
#include "DHT22Utils.h"
#include "DisplayUtils.h"

#define DHTPIN_PRIMARY 14

BMPUtils bmpManager;
DHT22Utils dht22ManagerPrimary(DHTPIN_PRIMARY);

void setup() {
  
  DisplayUtils::init();
  DisplayUtils::createLayout();

  Wire.begin();
  bmpManager.initBMP();

  DisplayUtils::printCalender();

}


void loop() {
  printHumidity(65, 2);
  printPressure(65, 11);
  printDuePoint(65, 30);
  delay(30000);
}

void printError(String s) {
  GLCD.CursorTo(15, 7);
  GLCD.print(s);
}

void printCurrentTime(int hour, int min, int sec) {
}

void printHumidity(int xOrigin, int yOrigin) {
 DHT22Data data = dht22ManagerPrimary.readRHValue();
 GLCD.CursorToXY(xOrigin, yOrigin);
 if (data.msg != NULL) {
   printError(data.msg);
 } else {
  GLCD.print("H:" + String(data.rh,1));
 }
}

void printPressure(int xOrigin, int yOrigin) {
  BMPData data = bmpManager.getPressureTempData();
  if (data.msg != NULL) {
    printError(data.msg);
  } else {
    GLCD.CursorToXY(xOrigin, yOrigin);
    GLCD.print("T:" + String(data.temp,1));
    GLCD.CursorToXY(xOrigin, yOrigin + 10);
    GLCD.print("P:" + String(data.pressure,1));
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
