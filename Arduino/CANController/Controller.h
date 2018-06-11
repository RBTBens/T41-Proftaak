#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Sensor.h"
#include <FastPID.h>

#define PUMP_SINGLE_SUPPLY 5
#define PUMP_DELAY 60000

enum ControllerType {
  NOT_DEFINED,
  TEMPERATURE,
  SOIL,
  LIGHT,
};

class Controller
{
  public:
    virtual void Regulate() = 0;
    virtual float GetValue() = 0;
    ControllerType GetType() {
      return type;
    }
    void SetDesiredValue(float value) {
      desiredValue = value;
    }
    int GetDesiredValue(){
      return desiredValue;
    }
    float desiredValue = -1;
  private:
    ControllerType type;
};

class TemperatureController : public Controller
{
  public:
    TemperatureController(/*iHeater* heater,*/ iTemperature* temp);
    void Regulate();
    float GetValue();

  private:
    FastPID myPID;
    void On();
    void Off();
    iHeater* heater;
    iTemperature* temp;
    int desiredValue;

};
class SoilController : public Controller
{
  public:
    SoilController(iPump* pump, iSoil* soil);
    void Regulate();
    float GetValue();
    void CheckPump();

  private:
    void On();
    void Off();
    iPump* pump;
    iSoil* soil;
    unsigned long lastSupplied = 0;

};
class LightController : public Controller
{
  public:
    LightController(/*iLED led,*/iLDR* ldr);
    void Regulate();
    float GetValue();

  private:
    void On();
    void Off();
    //iLED led;
    iLDR* ldr;

};
#endif
