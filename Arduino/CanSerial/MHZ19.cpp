//
// Created by wouter on 6-4-18.
//

#include "MHZ19.h"
#include <SoftwareSerial.h>

SoftwareSerial* _serial;

MHZ19::MHZ19( int receivePin, int transmitPin )
{
  _serial = new SoftwareSerial( receivePin, transmitPin );
  _serial->begin(9600);
}

uint16_t MHZ19::getCO2()
{
  /* Clear buffer */
  while ( _serial->available() > 0 )
  {
    _serial->read();
  }
  // Send command and read response
  write( CMD_READ );
  delay(10);
  _serial->readBytes( response, 9 );

  //    Serial.println("MH-Z19 received:");
  //    for(int i = 0; i < 9; i++){
  //        Serial.print(response[i], HEX);
  //        Serial.print(", ");
  //    }
  //    Serial.println();

  // Check if response is valid
  if ( response[0] != 0xFF || response[1] != 0x86 || response[8] != calculateChecksum( response ) )
  {
    return 0;
  }

  uint16_t ppm = ( 256 * response[2] ) + response[3];
  return ppm;
}

void MHZ19::setRange( MHZ19::sensor_range range )
{
  // TODO: remove preset arrays
  const byte range2000[9] = {0xFF, 0x01, 0x99, 0x00, 0x00, 0x00, 0x07, 0xD0, 0x8F};
  const byte range5000[9] = {0xFF, 0x01, 0x99, 0x00, 0x00, 0x00, 0x13, 0x88, 0xCB};

  switch ( range )
  {
    case PPM_2000:
      _serial->write( range2000, 9 );
      break;
    case PPM_5000:
      _serial->write( range5000, 9 );
      break;
  }
}

void MHZ19::setABC( bool on )
{
  on ? write( CMD_ABC, ABC_ON ) : write( CMD_ABC, ABC_OFF );
}

void MHZ19::write( byte command, byte value )
{
  byte cmd[9] = {0xFF, 0x01, command, value, 0x00, 0x00, 0x00, 0x00, 0x00};
  cmd[8] = calculateChecksum( cmd );
  _serial->write( cmd, 9 );

  //    Serial.println("MH-Z19 command send:");
  //    for(int i = 0; i < 9; i++){
  //        Serial.print(cmd[i], HEX);
  //        Serial.print(", ");
  //    }
  //    Serial.println();
}

byte MHZ19::calculateChecksum( byte* packet )
{
  char checksum = 0;

  for ( int i = 1; i < 8; i++ )
  {
    checksum += packet[i];
  }

  checksum = 0xff - checksum;
  checksum += 1;
  return ( byte ) checksum;
}
