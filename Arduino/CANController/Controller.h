#ifndef CONTROLLER_H 
#define CONTROLLER_H

#include "Sensor.h"

enum ControllerType{
  NOT_DEFINED,
  TEMPERATURE,
  SOIL,
  LIGHT,
};
  
class Controller
{
  struct Recipe{
    int DesiredTemperature;
    int DesiredLight;
    int DesiredMoisture;
  };
  
  public:
    void Regulate(){};
    virtual float GetValue() = 0;
    void SetRecipe(Recipe rec) { recipe = rec; }
    Recipe GetRecipe() { return recipe; }
    ControllerType GetType() { return type; }
  private:
    Recipe recipe;
    ControllerType type;
};

class TemperatureController : public Controller
{
  public: 
  TemperatureController(/*iHeater heater, */iTemperature* temp);
  void Regulate();
  float GetValue();
  
  private:
  void On();
  void Off();
  //iHeater heater;
  iTemperature* temp;
  
};
class SoilController : public Controller
{
  public: 
  SoilController(/*iPump pump,*/ /*iSoil* soil*/);
  void Regulate();
  float GetValue();
  
  private:
  void On();
  void Off();
  //iPump pump;
  iSoil* soil;
  
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
