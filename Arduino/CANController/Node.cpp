#include "Node.h"

Node::Node()
{
  controllerType = IdentifySensor();
  
  switch (controllerType)
  {
    case NOT_DEFINED:
    {
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
      controller = new SoilController();
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
      return NOT_DEFINED;
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
  if ( !lux.begin() )
    {
        return false;
    }

    /* You can also manually set the gain or enable auto-gain support */
    // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
    // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
    lux.enableAutoRange( true );          /* Auto-gain ... switches automatically between 1x and 16x */

    /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
    // tsl.setIntegrationTime( TSL2561_INTEGRATIONTIME_13MS ); /* fast but low resolution */
    lux.setIntegrationTime( TSL2561_INTEGRATIONTIME_101MS );  /* medium resolution and speed   */
    // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */
#if DEBUG
    /* Update these values depending on what you've set above! */
    Serial.println( "-- TSL2561 --" );
    Serial.print( "Gain:   " );
    Serial.println( "Auto" );
    Serial.print( "Timing: " );
    Serial.println( "101 ms" );
    Serial.println();
#endif
    return true;
}

bool Node::testTemp()
{
  if ( !temp.begin( 0x76 ) )
    {
        return false;
    }

    temp.setSampling( Adafruit_BME280::MODE_FORCED,   // in sleep mode when not in use
                     Adafruit_BME280::SAMPLING_X1,   // temperature
                     Adafruit_BME280::SAMPLING_NONE, // pressure
                     Adafruit_BME280::SAMPLING_X1,   // humidity
                     Adafruit_BME280::FILTER_OFF );
#if DEBUG
    Serial.println( "-- BME280 --" );
    Serial.println( "1x temperature / 1x humidity / 0x pressure oversampling" );
    Serial.println( "forced mode, filter off" );
    Serial.println();
#endif
    return true;
}

bool Node::testSoil()
{
  return false;
}

bool Node::testCo2()
{
   co2.setRange(MHZ19::PPM_2000);    // 0-2000 PPM
}

void Node::Regulate()
{
  controller->Regulate();
}

float Node::GetValue()
{
  return controller->GetValue();
}

