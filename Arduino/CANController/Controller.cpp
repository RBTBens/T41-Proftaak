#include "Controller.h"

TemperatureController::TemperatureController(/*iHeater* heater,*/ iTemperature* temp) : temp(temp)
{
  pid = new AutoPID(&temperaturePID, &setPoint, &outputVal, TEMPERATURE_OUTPUT_MIN, TEMPERATURE_OUTPUT_MAX, TEMPERATURE_KP, TEMPERATURE_KI, TEMPERATURE_KD);
  pid->setBangBang(1);
  pid->setTimeStep(1000);
}

void TemperatureController::Regulate()
{
  setPoint = GetDesiredValue();
  temperaturePID = temp->GetValue();
  
  if (setPoint < 0)
  {
    analogWrite(HEATERPIN, 0);
  }
  else
  {
    pid->run();
    analogWrite(HEATERPIN, outputVal);
    
    Serial.print("Feedback: ");
    Serial.print(temperaturePID);
    Serial.print(" output: ");
    Serial.println(outputVal);
  }
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

SoilController::SoilController(iPump* pump, iSoil* soil)
{
  this->soil = soil;
  this->pump = pump;
}

void SoilController::Regulate()
{
  if (GetValue() < desiredValue)
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
  unsigned long current = millis();
  if (current - lastSupplied > PUMP_DELAY)
  {
    pump->Supply(PUMP_SINGLE_SUPPLY);
    lastSupplied = current;
  }
}
void SoilController::Off()
{
  pump->Off();
}

void SoilController::CheckPump()
{
  pump->Check();
}

LightController::LightController(/*iLED led,*/iLDR* ldr) : ldr(ldr)
{

}

void LightController::Regulate()
{
  if (GetValue() > desiredValue)
  {
    On();
  }
  else if (GetValue() < desiredValue)
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


