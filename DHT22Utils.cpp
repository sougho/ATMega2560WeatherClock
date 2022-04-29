#include "DHT22Utils.h"

DHT22Data DHT22Utils::readRHValue() { 
  float h =_m_dht->readHumidity();
  float t = _m_dht->readTemperature();
  if (!isnan(h) && !isnan(t)) {
   return DHT22Data (t, h, NULL);
  } else {
    return DHT22Data(-1, -1, "DHT-E:01");
  }
}

DHT22Utils::DHT22Utils(int pin) {
  _m_dht = new DHT(pin, DHTTYPE);
  _m_dht->begin();
}
