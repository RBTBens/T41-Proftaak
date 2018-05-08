#include "Sensor.h"

BME::BME(Adafruit_BME280 bme) : bme(bme)
{
  
}

float BME::GetValue()
{
  bme.takeForcedMeasurement();
  return bme.readTemperature();
}

float SOIL::GetValue()
{
  //Nog niet klaar.
  return 0;
}

TSL::TSL(Adafruit_TSL2561_Unified tsl) : tsl(tsl)
{
  
}

float TSL::GetValue()
{
  uint16_t broadband, ir;
  tsl.getLuminosity( &broadband, &ir );
  uint32_t lux = tsl.calculateLux( broadband, ir );
  return (float)lux;
}

