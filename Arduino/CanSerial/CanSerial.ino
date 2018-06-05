#include <CAN.h>
#include "CanSerial.h"
#include "MHZ19.h"

#define PIN_RX 6
#define PIN_TX 7

#define UPDATE_DELAY 30000

// declared Variables
//  bioSphere node
//  000000000 00 = PI
//            01 = Temperature
//            10 = Light
//            11 = Soil

const int nodeId = 0;
unsigned long lastUpdate = 0;

CanSerial serial;
MHZ19 co2(PIN_RX, PIN_TX);

void WriteWithID( message_t message )
{
  if ( message.messageSize < 9 )
  {
    CAN.beginPacket( message.id );
    for ( int i = 0; i < message.messageSize; i++ )
    {
      CAN.write( message.message[i] );
    }
    CAN.endPacket();
  }
}

void onReceive( int packetSize )  // received a packet
{
  Serial.println("eypik");
  if (CAN.packetRtr()) {
      Serial.println("OH BOY");
      return;
    }
  if ( CAN.packetId() == nodeId )
  {
    
    
    message_t message = {0};
    message.id = ( char ) CAN.read();
    int counter = 0;
    while ( CAN.available() )
    {
      message.message[counter] = ( char ) CAN.read();
      counter++;
    }
    message.messageSize = counter;
    serial.write( message );
  }
}

void setup()
{
  serial.begin(); // Initialised on 15200
  co2.setRange(MHZ19::PPM_5000);
  // Setup the CAN bus
  CAN.begin( 500E3 );
  CAN.onReceive( onReceive );
}

void loop()
{
  message_t receivedMessage = serial.read();
  if ( receivedMessage.id > 0 )
  {
    WriteWithID( receivedMessage );
  }

  if (millis() - lastUpdate >= UPDATE_DELAY) {
    lastUpdate = millis();
    uint16_t result = co2.getCO2();
    String temp = String(result);
    message_t message = {0};
    message.id = 0;
    temp.toCharArray(message.message, 8);
    message.messageSize = temp.length();
    serial.write( message );
  }
}
