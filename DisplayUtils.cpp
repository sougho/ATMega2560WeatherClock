#include "DisplayUtils.h"

#define ORIGIN 0
#define RIGHT_RECTANGLE_DIVIDER 39
#define CALENDER_DATE_SEPARATOR 3
#define CALENDER_NO_COLS 7
#define DIGIT_FONT_WIDTH 5
#define DIGIT_FONT_HEIGHT 7
#define CALENDER_LINE_SEPARATOR 2
#define VERTICAL_OFFSET 10

char   daysOfWeek[7][2] = {"M", "T", "W", "T", "F", "S", "S"};



// Image_t bmOne = OneBitmap;

void DisplayUtils::createLayout(void) {
  // GLCD.DrawRect(ORIGIN, ORIGIN, GLCD.Width / 2 - 1, GLCD.Height - 1);
  // GLCD.DrawRect(GLCD.CenterX - 1, 0, GLCD.Width / 2 , GLCD.Height - 1);
  GLCD.DrawLine(90, 0, 90, 63);
  GLCD.DrawLine(90, 31, 127, 31);
}

void DisplayUtils::init() {
  GLCD.Init();
  GLCD.SelectFont(System5x7);
}

void DisplayUtils::printCalender(int originDayOfWeek, int daysInMonth, int currentDate) {
    for (int i = 0; i< 7; i++) {
      GLCD.CursorToXY(i *  (CALENDER_DATE_SEPARATOR + 2 * DIGIT_FONT_WIDTH) + DIGIT_FONT_WIDTH, 1);
      GLCD.print(daysOfWeek[i]);
    }
    for (int i = originDayOfWeek; i < daysInMonth + originDayOfWeek ; i++) {
      GLCD.CursorToXY((i%CALENDER_NO_COLS) *  (CALENDER_DATE_SEPARATOR + 2* DIGIT_FONT_WIDTH) + ((i-originDayOfWeek) < 9?DIGIT_FONT_WIDTH:0) , 
        VERTICAL_OFFSET + (i/7) * (  DIGIT_FONT_HEIGHT + CALENDER_LINE_SEPARATOR));
        if (currentDate == (i  - originDayOfWeek + 1)) 
          GLCD.print("\"");
        else 
          GLCD.print(i  - originDayOfWeek + 1);
    }
}

void DisplayUtils::printCurrentTime(int hr24, int mn, int ss, boolean is12Hr) {
  GLCD.FillRect(90,63, 126, 126, WHITE);
  GLCD.SelectFont(Arial_bold_14);

  // Clear the hour area
  GLCD.CursorToXY(92, 38);
  GLCD.print("       ");
  
  GLCD.CursorToXY(92, 38);
  int adjHr = ((is12Hr)?  (hr24 > 12)? hr24-12 : hr24   :  hr24);
  GLCD.print((adjHr < 10)? "0" + String(adjHr) : String(adjHr));
  GLCD.print(":");
  GLCD.print((mn < 10)? "0" + String(mn) : String(mn));

  // Clear the seconds area
  
  GLCD.CursorToXY(97, 49);
  GLCD.print("   ");
  GLCD.CursorToXY(97, 49);
  GLCD.print((ss < 10)? "0" + String(ss) : String(ss));
 
  GLCD.SelectFont(System5x7);
  if ((is12Hr) && (hr24 > 12)) {
    GLCD.CursorToXY(116, 53);
    GLCD.print("PM");
  }
}
