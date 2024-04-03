#include "MainPage.h"
#include "Time.h"
#include "BMPUtils.h"
#include "DHT22Utils.h"
#include "DisplayUtils.h"

#define ORIGIN 0
#define RIGHT_RECTANGLE_DIVIDER 39
#define CALENDER_DATE_SEPARATOR 7
#define CALENDER_NO_COLS 7
#define DIGIT_FONT_WIDTH 3
#define DIGIT_FONT_HEIGHT 5
#define CALENDER_LINE_SEPARATOR 4
#define VERTICAL_OFFSET 10

#define DHTPIN_PRIMARY 14

#define SENSOR_READ_INTERVAL 300 /* 5 minutes */


BMPUtils bmpManager;
DHT22Utils dht22ManagerPrimary(DHTPIN_PRIMARY);

char   daysOfWeek[7][2] = {"M", "T", "W", "T", "F", "S", "S"};
int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char months[12][4] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};



long secCounter = 0;


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
    GLCD.print("H:" + String(data.rh, 1));
//    GLCD.CursorToXY(xOrigin, yOrigin + 10);
//    GLCD.print("T:" + String(data.temp, 1));
  }
}

void printPressure(int xOrigin, int yOrigin) {
  BMPData data = bmpManager.getPressureTempData();
  if (data.msg != NULL) {
    printError(data.msg);
  } else {
    GLCD.CursorToXY(xOrigin, yOrigin);
    GLCD.print("T:" + String(data.temp, 1));
    GLCD.CursorToXY(xOrigin, yOrigin + 10);
    GLCD.print("P:" + String(data.pressure, 1));
  }
}

// Image_t bmOne = OneBitmap;

void createLayout(void) {
  // GLCD.DrawRect(ORIGIN, ORIGIN, GLCD.Width / 2 - 1, GLCD.Height - 1);
  // GLCD.DrawRect(GLCD.CenterX - 1, 0, GLCD.Width / 2 , GLCD.Height - 1);
  GLCD.DrawLine(89, 0, 89, 63);
  GLCD.DrawLine(89, 31, 127, 31);
}




void printCalender(int originDayOfWeek, int month, int currentDate, int year) {
    
    int dayInThisMonth = daysInMonth[month - 1];

    // Check leap year
    if ((month == 2) && (currentDate == 29))
    {
      dayInThisMonth = 29;
    }
    
    for (int i = 0; i< 7; i++) {
      GLCD.CursorToXY(i *  (CALENDER_DATE_SEPARATOR + 2 * DIGIT_FONT_WIDTH) + DIGIT_FONT_WIDTH, 1);
      GLCD.print(daysOfWeek[i]);
    }
    for (int i = originDayOfWeek; i < dayInThisMonth + originDayOfWeek ; i++) {
      GLCD.CursorToXY((i%CALENDER_NO_COLS) *  (CALENDER_DATE_SEPARATOR + 2* DIGIT_FONT_WIDTH) + ((i-originDayOfWeek) < 9?DIGIT_FONT_WIDTH:0) +1, 
        VERTICAL_OFFSET + (i/7) * (  DIGIT_FONT_HEIGHT + CALENDER_LINE_SEPARATOR));
        if (currentDate == (i  - originDayOfWeek + 1)) {
         if ((i-originDayOfWeek) < 9)
         GLCD.DrawRect((i%CALENDER_NO_COLS) *  (CALENDER_DATE_SEPARATOR + 2* DIGIT_FONT_WIDTH) + ((i-originDayOfWeek) < 9?DIGIT_FONT_WIDTH:0) -2,
          VERTICAL_OFFSET + (i/7) * (  DIGIT_FONT_HEIGHT + CALENDER_LINE_SEPARATOR) -2, 
          7, 8);
          else 
          GLCD.DrawRect((i%CALENDER_NO_COLS) *  (CALENDER_DATE_SEPARATOR + 2* DIGIT_FONT_WIDTH) + ((i-originDayOfWeek) < 9?DIGIT_FONT_WIDTH:0),
          VERTICAL_OFFSET + (i/7) * (  DIGIT_FONT_HEIGHT + CALENDER_LINE_SEPARATOR) -2, 
          9, 8);
        }
        GLCD.print(i  - originDayOfWeek + 1);
    }
    GLCD.DrawRect(21, 54, 48, 8);
    GLCD.CursorToXY(24, 56);

    GLCD.print(currentDate);
    if (currentDate > 9) { 
      GLCD.print(" ");
    } else {
      GLCD.print("  ");
    }
    GLCD.print(months[month -1]);
    GLCD.print(" ");
    GLCD.print("20");
    GLCD.print(year);
}

void printCurrentTime(int hr24, int mn, int ss, boolean is12Hr) {
  
  GLCD.FillRect(90,63, 126, 126, WHITE);
  GLCD.SelectFont(Arial_bold_14);

  // Clear the hour area
  GLCD.CursorToXY(92, 38);
  GLCD.print("       ");
  
  GLCD.CursorToXY(92, 38);
  
  int adjHr = ((is12Hr)?  (hr24 > 12)? hr24-12 : (hr24 == 0)? 12 : hr24   :  hr24);
  
  GLCD.print((adjHr < 10)? "0" + String(adjHr) : String(adjHr));
  GLCD.print(":");
  GLCD.print((mn < 10)? "0" + String(mn) : String(mn));

  // Clear the seconds area
  
  GLCD.CursorToXY(97, 49);
  GLCD.print("   ");
  GLCD.CursorToXY(97, 49);
  GLCD.print((ss < 10)? "0" + String(ss) : String(ss));

  GLCD.SelectFont(Wendy3X5);
  if ((is12Hr) && (hr24 >= 12)) {
    GLCD.CursorToXY(116, 53);
    GLCD.print("PM");
  }
}
displayClockInitPage() {
  AClkTime currTime = readCurrentTimeValue();
  printCalender(currTime.firstDayOfMonth, currTime.month, currTime.day, currTime.year);
  printCurrentTime(currTime.hr24, currTime.mn, currTime.ss, true);
  printHumidity(92, 2);
  printPressure(92, 11);
}

void displayClockPageOne() {
  AClkTime currTime = readCurrentTimeValue();
  if ((currTime.hr24 == 0) && (currTime.mn == 0) && ( currTime.ss <= 2))
  {
    GLCD.ClearScreen();
    createLayout();
    printCalender(currTime.firstDayOfMonth, currTime.month, currTime.day, currTime.year);
    printHumidity(92, 2);
    printPressure(92, 11);
  }
  printCurrentTime(currTime.hr24, currTime.mn, currTime.ss, true);
  secCounter++;
  if (secCounter == SENSOR_READ_INTERVAL) {
    printHumidity(92, 2);
    printPressure(92, 11);
    secCounter = 0;
  }
}


 void MainPage::handleEvent(EVENTS event){
  if (event != RENDER) {
    GLCD.ClearScreen();
    GLCD.SelectFont(Wendy3X5);
    displayClockInitPage();
  }
  displayClockPageOne();
 }
