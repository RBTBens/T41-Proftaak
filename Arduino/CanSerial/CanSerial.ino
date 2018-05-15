#include <CAN.h>
#include "CanSerial.h"

// declared Variables
//  bioSphere node
//  000000000 00 = PI
//            01 = Temperature
//            10 = Light
//            11 = Soil

const int nodeId = 0;

CanSerial serial;

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
    if ( CAN.packetId() == nodeId )
    {
        message_t message = {0};
        int       counter = 0;
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
}
