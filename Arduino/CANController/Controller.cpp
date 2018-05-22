#include "Controller.h"

TemperatureController::TemperatureController(/*iHeater heater, */iTemperature* temp) : temp(temp)
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

SoilController::SoilController(/*iPump pump,*/ iSoil* soil)
{
  this->soil = soil;
}

void SoilController::Regulate()
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

float SoilController::GetValue()
{
  return soil->GetValue();
}
void SoilController::On()
{
  //led.On();
}
void SoilController::Off()
{
  //led.Off();
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


