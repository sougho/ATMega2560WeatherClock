struct AClkTime {
  int hr24;
  int mn;
  int ss;
  int day;
  int month;
  int dayOfWeek;
  int year;
  int firstDayOfMonth;

  int computeFirstDayOfMonth() {
   return subtractMod7( dayOfWeek, day % 7);
  }

  int subtractMod7(int a, int b) {
    return (a - (b-1)) < 0 ? (a - (b -1)) + 7 : (a - (b -1));
  }
};

AClkTime readCurrentTimeValue();
void setToCompileTime();
