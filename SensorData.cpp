#include <Arduino.h>
#include "SensorData.h"
#include "BMPUtils.h"
#include "DHT22Utils.h"
#include "DisplayUtils.h"

#define DHTPIN_PRIMARY 14
BMPUtils bmpManager;
DHT22Utils dht22ManagerPrimary(DHTPIN_PRIMARY);


SensorData currentSensorData;
SensorData shortTermSensorTrend[24];

void readSensors() {

  float t1 = 0;
  float t2 = 0;

  BMPData dataPress = bmpManager.getPressureTempData();
 
  if (dataPress.msg != NULL) {
    printError(dataPress.msg);
  } else {
    currentSensorData.pressure = dataPress.pressure;
    t1 = dataPress.temp;
  }

  DHT22Data dataHumid = dht22ManagerPrimary.readRHValue();
  if (dataHumid.msg != NULL) {
    printError(dataHumid.msg);
  } else {
   currentSensorData.humidity = dataHumid.rh;
   t2 = dataHumid.temp;
  }

  currentSensorData.temparature = t1;
}