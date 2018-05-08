#ifndef EEPROM_ACCESSOR_H
#define EEPROM_ACCESSOR_H

#include "Arduino.h"
#include <EEPROM.h>

class EepromAccessor {
  public:
    int WriteID(int id);
    int GetID();
};

#endif

