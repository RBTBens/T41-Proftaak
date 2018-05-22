#ifndef SENSOR_H 
#define SENSOR_H

#include "Adafruit_TSL2561_U.h"
#include "Adafruit_BME280.h"
#include "MHZ19.h"

class iTemperature
{
  public:
  ~iTemperature(){};
  virtual float GetValue() = 0;
};

class BME : public iTemperature
{
  public:
  BME(Adafruit_BME280 bme);
  float GetValue() override;
  private:
  Adafruit_BME280 bme;
  
};

class iSoil
{
  public:
  ~iSoil(){};
  virtual float GetValue() = 0;
};

class Soil : public iSoil
{
  public:
  Soil();
  float GetValue() override;
};

class iLDR
{
  public:
  ~iLDR(){};
  virtual float GetValue() = 0;
};

class TSL : public iLDR
{
  public:
  TSL(Adafruit_TSL2561_Unified tsl);
  float GetValue() override;
  private:
  Adafruit_TSL2561_Unified tsl;
};
#endif
