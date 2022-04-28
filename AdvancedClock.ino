#include <DHT.h>
#include <DHT_U.h>

#include <glcd.h>
#include <glcd_Buildinfo.h>
#include <glcd_Config.h>
#include <fonts/allFonts.h>

#include <Arduino.h>
#include <Wire.h>

#include "BMPUtils.h"
#include "DHT22Utils.h"

#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

BMPUtils bmpManager;
DHT22Utils dht22Manager;

void setup() {

  GLCD.Init();
  createLayout();
  GLCD.SelectFont(System5x7);
  
  dht22Manager.init();
  
  Wire.begin();
  bmpManager.initBMP();

}

// Layout Defintions
#define RIGHT_RECTANGLE_DIVIDER 38
#define ORIGIN 0

void createLayout() {
  GLCD.DrawRect(ORIGIN, ORIGIN, GLCD.Width / 2 - 1, GLCD.Height -1);
  GLCD.DrawRect(GLCD.CenterX - 1, 0, GLCD.Width/2 , GLCD.Height -1);
  GLCD.DrawLine(GLCD.CenterX - 1, RIGHT_RECTANGLE_DIVIDER, GLCD.Width -2 , RIGHT_RECTANGLE_DIVIDER);
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
 DHT22Data data = dht22Manager.readRHValue();
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
