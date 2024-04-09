#include "DisplayUtils.h"
#include "Time.h"
#include "BMPUtils.h"
#include "DHT22Utils.h"
#include "ModeHandlers.h"


// Image_t bmOne = OneBitmap;

void displayInit() {
  GLCD.Init(WHITE);
  GLCD.SelectFont(Wendy3X5);
}

void printError(String s) {
  GLCD.CursorTo(15, 7);
  GLCD.print(s);
}