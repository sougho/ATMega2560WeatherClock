#include "BMPUtils.h"

#include <glcd.h>
#include <glcd_Buildinfo.h>
#include <glcd_Config.h>
#include <fonts/allFonts.h>


BMPData BMPUtils::getPressureTempData()  {

  // Read Temparature
  
  if (!_m_bmpSensor->measureTemperature())
  {
    return BMPData(-1, -1, "BMP-E:01");
  }
  do
  {
    delay(100);
  } while (!_m_bmpSensor->hasValue());

  float temp = _m_bmpSensor->getTemperature();

  // Read Pressure

  if (!_m_bmpSensor->measurePressure())
  {
    return BMPData(-1, -1, "BMP-E:02");
  }

  do
  {
    delay(100);
  } while (!_m_bmpSensor->hasValue());

  
  Serial.print(_m_bmpSensor->getPressure());
  

  return BMPData(temp, _m_bmpSensor->getPressure() / 100);
}




BMPData BMPUtils::initBMP() {
  if (!_m_bmpSensor->begin())
  {
     return BMPData(-1, -1, "BMP-E:00");
  }
  _m_bmpSensor->resetToDefaults();
  _m_bmpSensor->setSamplingMode(BMP180MI::MODE_UHR);
  return BMPData(-1,-1);
}
