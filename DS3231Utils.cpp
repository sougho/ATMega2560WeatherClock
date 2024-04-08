#include <DS3231.h>
#include "Time.h"

bool century = false;
bool h12Flag;
bool pmFlag;

DS3231 _s_clk;

AClkTime readCurrentTimeValue() {

  AClkTime currTime;

  currTime.mn = _s_clk.getMinute();
  currTime.hr24 = _s_clk.getHour(h12Flag, pmFlag);
  currTime.ss = _s_clk.getSecond();

  currTime.day = _s_clk.getDate();
  currTime.month =  _s_clk.getMonth(century);
  
  // Monday goes as 7, whereas for us it's 0
  currTime.dayOfWeek = _s_clk.getDoW() % 7;
  currTime.year =  _s_clk.getYear();

  currTime.firstDayOfMonth = currTime.computeFirstDayOfMonth();
  return currTime;
}

void setToCompileTime() {

  int hr;
  int mn;
  int sec;

  sscanf(__TIME__, "%d:%d:%d", &hr, &mn, &sec);
  
  sec += 10;
  if (sec > 60) {
    sec = sec - 60;
    mn++;
  }

  _s_clk.setHour(hr);
  _s_clk.setMinute(mn);
  _s_clk.setSecond(sec+10);
  _s_clk.setDate(19);
  _s_clk.setDoW(1);
  _s_clk.setMonth(3);
  _s_clk.setYear(24);
}
