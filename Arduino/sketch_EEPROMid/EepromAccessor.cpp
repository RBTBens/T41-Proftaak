#include "Arduino.h"
#include "EepromAccessor.h"

int EepromAccessor::WriteID(int id) {
     int addr = 0;
     EEPROM.write(addr, id);
}

int EepromAccessor::GetID() {
    int addr = 0;
    int value = EEPROM.read(addr);
    //TODO: Check if int is valid value
    return value;
}
