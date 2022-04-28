#include "DHT22Utils.h"

void DHT22Utils::init() {
  _m_dht->begin();
}

DHT22Data DHT22Utils::readRHValue() { 
  float h =_m_dht->readHumidity();
  float t = _m_dht->readTemperature();
  if (!isnan(h) && !isnan(t)) {
   return DHT22Data (t, h, NULL);
  } else {
    return DHT22Data(-1, -1, "DHT-E:01");
  }
}
