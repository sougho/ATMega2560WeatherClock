#include "EEPROM.h"
#include <Arduino.h>

void EEPROM::writeEEPROM(unsigned int eeaddress, unsigned short data ) {
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(eeaddress >> 8));      //writes the MSB
  Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
  Wire.write(data);
  Wire.endTransmission();
}

unsigned short EEPROM::readEEPROM(unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(eeaddress >> 8));      //writes the MSB
  Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
  Wire.endTransmission();
  Wire.requestFrom(EEPROM_I2C_ADDRESS,1);
  if (Wire.available()) 
    rdata = Wire.read();
  return rdata;
}
