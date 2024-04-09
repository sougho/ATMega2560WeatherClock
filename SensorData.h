#ifndef __SENSORDATA_H_
#define __SENSORDATA_H_
#include <Arduino.h>
#include "BMPUtils.h"
#include "DHT22Utils.h"

const int pressureOrigin  = 900;
struct CurrentSensorData {
  float pressure; 
  float temparature;
  float humidity;
};

extern CurrentSensorData currentSensorData;

void readSensors();
#endif