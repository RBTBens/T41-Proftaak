#include "Controller.h"

TemperatureController::TemperatureController(/*iHeater* heater,*/ iTemperature* temp) : temp(temp)
{
  float Kp = 1.1, Ki = 0.4, Kd = 0.1, Hz = 10;
  int output_bits = 8;
  bool output_signed = false;
  myPID = FastPID(Kp, Ki, Kd, Hz, output_bits, output_signed);
}

void TemperatureController::Regulate()
{
  //  desiredValue = 40; // set to the new desired value // 40 is for testing
  int setpoint = desiredValue; //write new desired value into this
  int feedback = temp->GetValue();
  for (int i = 0; i < 30; i++)
  {
    uint8_t output = myPID.step(setpoint, feedback);
    // write output over PIN
    analogWrite(HEATERPIN, 255 - output);
  }

  Serial.print("temp: ");
  Serial.println(feedback);
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


