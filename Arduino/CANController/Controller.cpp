#include "Controller.h"

TemperatureController::TemperatureController(/*iHeater* heater,*/ iTemperature* temp) : temp(temp)
{
  
}

void TemperatureController::Regulate()
{
  if (GetValue() > GetRecipe().DesiredLight)
  {
    On();
  }
  else if (GetValue() < GetRecipe().DesiredLight)
  {
    Off();
  }
  //ja
}

float TemperatureController::GetValue()
{
  return temp->GetValue();
}
void TemperatureController::On()
{
  //led.On();
}
void TemperatureController::Off()
{
  //led.Off();
}

SoilController::SoilController(iPump* pump, iSoil* soil): pump(pump)
{
  this->soil = soil;
 // this->pump = pump;
}

void SoilController::Regulate()
{
  Serial.println("Soil::Regulate()");
  
  // For tracking exact pumpee
  pump->Regulate();

  float value = GetValue();
  if (value > desiredValue)
  {
    Off();
  }
  else if (value < desiredValue)
  {
    On();
  }
}

float SoilController::GetValue()
{
  return soil->GetValue();
}
void SoilController::On()
{
  pump->Supply(PUMP_SINGLE_SUPPLY);
}
void SoilController::Off()
{
  pump->Off();
}


LightController::LightController(/*iLED led,*/iLDR* ldr) : ldr(ldr)
{
  
}

void LightController::Regulate()
{
  if (GetValue() > GetRecipe().DesiredLight)
  {
    On();
  }
  else if (GetValue() < GetRecipe().DesiredLight)
  {
    Off();
  }
  //ja
}

float LightController::GetValue()
{
  return ldr->GetValue();
}
void LightController::On()
{
  //led.On();
}
void LightController::Off()
{
  //led.Off();
}


