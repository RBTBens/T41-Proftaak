#include "Sensor.h"

Heater::Heater()
{

}

void Heater::On()
{
  
}

void Heater::Off()
{
  
}

Pump::Pump()
{
  
}

void Pump::On()
{
  digitalWrite(PUMPPIN, HIGH);
}

void Pump::Off()
{
  digitalWrite(PUMPPIN, LOW);
}

BME::BME(Adafruit_BME280 bme) : bme(bme)
{
  
}

float BME::GetValue()
{
  bme.takeForcedMeasurement();
  return bme.readTemperature();
}

Soil::Soil()
{
  
}

float Soil::GetValue()
{
  pinMode(SOILPIN, INPUT);
  digitalWrite(SOILPIN, HIGH);
  float value = analogRead(SOILPIN);

    if (value > 1000)
    {
      return -1;
    }
  return constrain(map(value, 300, 600, 100, 0), 0, 100);
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

