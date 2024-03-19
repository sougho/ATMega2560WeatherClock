#include <Wire.h>

#define EEPROM_I2C_ADDRESS 0x50

class EEPROM {
  public: 
  void writeEEPROM(unsigned int eeaddress, unsigned short data );
  unsigned short readEEPROM(unsigned int eeaddress );
};
