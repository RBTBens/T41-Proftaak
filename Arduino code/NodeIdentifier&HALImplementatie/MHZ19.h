//
// Created by wouter on 6-4-18.
//

#ifndef WEATHER_STATION_MHZ19_H
#define WEATHER_STATION_MHZ19_H

#include "Arduino.h"

class MHZ19
{
public:
    enum sensor_range {
        PPM_2000,
        PPM_5000
    };

    enum sensor_command {
        CMD_READ = 0x86,
        CMD_ABC = 0x79
    };

    enum command_value {
        ABC_ON = 0xA0,
        ABC_OFF = 0x00
    };

    MHZ19(int receivePin, int transmitPin);
    void setRange(sensor_range range);
    uint16_t getCO2();
private:
    byte response[9];

    void write(byte command, byte value = 0x00);
    void setABC(bool on);   // Experimental function
    byte calculateChecksum(byte* packet);
};

#endif //WEATHER_STATION_MHZ19_H
