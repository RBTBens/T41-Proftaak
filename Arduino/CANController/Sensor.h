#ifndef SENSOR_H 
#define SENSOR_H
#define PUMPPIN 4
#define HEATERPIN 3
#define SOILPIN A0
#define SOIL_STARTUP 3

#include "Adafruit_TSL2561_U.h"
#include "Adafruit_BME280.h"

class iPump
{
  public:
  ~iPump() {};
  virtual void On() = 0;
  virtual void Off() = 0;
  virtual void Supply(float ml) = 0;
  virtual void Check() = 0;
};

class Pump : public iPump
{
  public:
  Pump();
  void On() override;
  void Off() override;
  void Supply(float ml) override;
  void Check() override;

  private:
  const float rate = 1.22f; // amount of ml per second (ml/s)
  unsigned long endMillis = 0;
  unsigned long passedMillis = 0;
};

class iHeater
{
  public:
  ~iHeater() {};
  virtual void On() = 0;
  virtual void Off() = 0;
};

class Heater : public iHeater
{
  public:
  Heater();
  void On() override;
  void Off() override; 
};

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

  private:
  bool pinEnabled = false;
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
