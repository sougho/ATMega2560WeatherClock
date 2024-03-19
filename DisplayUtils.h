#include <glcd.h>
#include <glcd_Buildinfo.h>
#include <glcd_Config.h>
#include <fonts/allFonts.h>

class DisplayUtils {
  public:
    static void init();
    static void createLayout();
    static void printCalender(int, int, int, int);
    static void printCurrentTime(int, int, int, boolean);
    static void displayClockPageOne();
    static void displayClockInitPage();
    static void displayClockPage2();
};
