#include <Wire.h>

#define EEPROM_I2C_ADDRESS 0x50

class EEPROM {
  public: 
  static void writeEEPROM(unsigned int eeaddress, unsigned short data );
  static unsigned short readEEPROM(unsigned int eeaddress );
};
