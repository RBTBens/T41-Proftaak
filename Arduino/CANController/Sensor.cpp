#include "Sensor.h"

Heater::Heater()
{
  pinMode(HEATERPIN, OUTPUT);
}

void Heater::On()
{
  
}

void Heater::Off()
{
  
}

Pump::Pump()
{
  pinMode(PUMPPIN, OUTPUT);
  digitalWrite(PUMPPIN, LOW);
}

void Pump::On()
{
  digitalWrite(PUMPPIN, HIGH);
}

void Pump::Off()
{
  digitalWrite(PUMPPIN, LOW);
}

void Pump::Supply(float ml)
{
  float ms = (ml / rate) * 1000.0f;
  Serial.print("Supplying ");
  Serial.print(ml);
  Serial.println(" ml");

  // Start interrupt timer on 1ms
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
  
  On();
  passedMillis = 0;
  endMillis = (unsigned long)ms;
}

void Pump::Check()
{
  if (endMillis > 0 && ++passedMillis >= endMillis)
  {
    Off();
    endMillis = 0;
    
    OCR0A = 0;
    TIMSK0 &= ~_BV(OCIE0A);
  }
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
  if (!pinEnabled)
  {
    pinMode(SOILPIN, INPUT);
    digitalWrite(SOILPIN, HIGH);
    pinEnabled = true;
    Serial.println("Enabled pin");
    for (int i = 0; i < SOIL_STARTUP; i++)
    {
      GetValue();
      delay(100);
    }
  }

  float value = analogRead(SOILPIN);
  if (value > 1000)
  {
    return -1;
  }

  return constrain(map(value, 300, 800, 100, 0), 0, 100);
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

