#include <Arduino.h>
#include "Time.h"
#include "Modes.h"
#include "LargeFormatTime.h"
#include "DisplayUtils.h"
#include "MemLocs.h"
#include "EEPROM.h"

extern char months[12][4];
char daysOfWeekLong[7][4] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

 void printCurrentTime2(int hr24, int mn, int ss, int month, int currentDate, int year, int dayOfWeek, boolean is12Hr) {
  
  GLCD.SelectFont(Verdana24);
  GLCD.FillRect(5,10, 114, 20, 0);
  
  GLCD.CursorToXY(5, 10);
  
  int adjHr = ((is12Hr)?  (hr24 > 12)? hr24-12 : (hr24 == 0)? 12 : hr24   :  hr24);
  
  GLCD.print((adjHr < 10)? "0" + String(adjHr) : String(adjHr));
  GLCD.print(":");
  GLCD.print((mn < 10)? "0" + String(mn) : String(mn));
  GLCD.print(":");
  GLCD.print((ss < 10)? "0" + String(ss) : String(ss));
 
  GLCD.SelectFont(Wendy3X5);
  if ((is12Hr) && (hr24 > 12)) {
    GLCD.CursorToXY(116, 20);
    GLCD.print("PM");
  }
    GLCD.CursorToXY(8, 46);

    GLCD.SelectFont(Arial_14);
    GLCD.print(daysOfWeekLong[dayOfWeek]);
    GLCD.print("  ");
    GLCD.print(currentDate);
    if (currentDate > 9) { 
      GLCD.print("  ");
    } else {
      GLCD.print("   ");
    }
    GLCD.print(months[month -1]);
    GLCD.print("  ");
    GLCD.print("20");
    GLCD.print(year);
}

 void LargeFormatTime::handleEvent(EVENTS event){
  if (event != RENDER) {
    GLCD.ClearScreen();
    EEPROM::writeEEPROM(CURR_DISPLAY_PAGE, 1);
  }
  AClkTime currTime = readCurrentTimeValue();
  printCurrentTime2(currTime.hr24, currTime.mn, currTime.ss, currTime.month, currTime.day, currTime.year, currTime.dayOfWeek, true);
 }
