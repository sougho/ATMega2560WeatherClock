#ifndef __SENSORDATA_H_
#define __SENSORDATA_H_
#include <Arduino.h>
#include "BMPUtils.h"
#include "DHT22Utils.h"

const int pressureOrigin  = 900;
struct SensorData {
  float pressure; 
  float temparature;
  float humidity;
};

extern SensorData currentSensorData;
extern SensorData shortTermSensorTrend[24];

void readSensors();
#endif