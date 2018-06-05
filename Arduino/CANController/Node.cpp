#include "Node.h"

Node::Node()
{
  controllerType = IdentifySensor();

  switch (controllerType)
  {
    case NOT_DEFINED:
      {
        Serial.println("Unable to identify controller type! Defaulting to Pi");
        break;
      }
    case TEMPERATURE:
      {
        Serial.println("Created Temperature Controller");
        controller = new TemperatureController(new BME(temp));
        break;
      }
    case LIGHT:
      {
        Serial.println("Created Light Controller");
        controller = new LightController(new TSL(lux));
        break;
      }
    case SOIL:
      {
        Serial.println("Created Soil Controller");
        controller = new SoilController(new Pump(), soil);
        break;
      }
  }
}

ControllerType Node::IdentifySensor()
{
  bool light = testLux();
  bool temperature = testTemp();
  bool soil = testSoil();

  testCo2();

  if (light)
  {
    return LIGHT;
  }
  else if (temperature)
  {
    return TEMPERATURE;
  }
  else if (soil)
  {
    return SOIL;
  }
  else
  {
    return NOT_DEFINED;
  }
}

int Node::GetIdentifier()
{
  switch (controllerType)
  {
    case TEMPERATURE:
      {
        return 0b001;
        break;
      }
    case LIGHT:
      {
        return 0b010;
        break;
      }
    case SOIL:
      {
        return 0b011;
        break;
      }
    default:
      {
        return 0b00;
        break;
      }
  }
}

bool Node::testLux()
{
  if (!lux.begin())
  {
    return false;
  }

  lux.enableAutoRange(true); // Auto-gain ... switches automatically between 1x and 16x
  lux.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS); // Medium sensor resolution and speed

  return true;
}

bool Node::testTemp()
{
  if (!temp.begin(0x76))
  {
    return false;
  }

  temp.setSampling(Adafruit_BME280::MODE_FORCED,   // in sleep mode when not in use
                   Adafruit_BME280::SAMPLING_X1,   // temperature
                   Adafruit_BME280::SAMPLING_NONE, // pressure
                   Adafruit_BME280::SAMPLING_X1,   // humidity
                   Adafruit_BME280::FILTER_OFF);

  return true;
}

bool Node::testSoil()
{
  if (soil == NULL)
  {
    soil = new Soil();
  }

  float value = soil->GetValue();
  return value >= 0 && value < 1000;
}

bool Node::testCo2()
{
  co2.setRange(MHZ19::PPM_2000); // 0-2000 PPM
}

void Node::Regulate()
{
  controller->Regulate();
}

void Node::SetDesiredValue(float value)
{
  controller->SetDesiredValue(value);
}

float Node::GetValue()
{
  return controller->GetValue();
}

int Node::GetDesiredValue()
{
  return controller->GetDesiredValue();
}

