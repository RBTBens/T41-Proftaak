#ifndef NODE_H 
#define NODE_H

#include "Adafruit_TSL2561_U.h"
#include "Adafruit_BME280.h"
#include "MHZ19.h"
#include "Controller.h"
#include "Sensor.h"

class Node
{
  public:
    Node(/*iCommunicationBus communication*/);
    int GetIdentifier();
    void Regulate();
    float GetValue();
    //Communication things
  private:
    Controller* controller;
    ControllerType controllerType;
    ControllerType IdentifySensor();
    
    bool testTemp();
    bool testSoil();
    bool testLux();
    bool testCo2();

    Soil* soil = NULL;
    MHZ19 co2 = MHZ19(2, 3);
    Adafruit_BME280 temp;
    Adafruit_TSL2561_Unified lux = Adafruit_TSL2561_Unified( TSL2561_ADDR_FLOAT );
};

#endif
