//
// Created by wk98 on 8-5-2018.
//

#include "Arduino.h"
#include "CanSerial.h"

void CanSerial::begin()
{
  Serial.begin( 9600 );
  msg_start = false;
  msg_valid = false;
  msg       = "";
}

void CanSerial::write( int8_t id, String message )
{
  String msg = "#";
  msg += id;
  msg += ":";
  msg += message;
  msg += ";";
  Serial.print( msg );
}

message_t CanSerial::read()
{
  while ( Serial.available() > 0 )
  {
    char incomming = Serial.read();
    if ( incomming == '#' )
    {
      msg       = "";
      msg_start = true;
    }
    else if ( incomming == ';' )
    {
      if ( msg_start )
      {
        msg_start = false;
        msg_valid = true;
        break;
      }
    }
    else if ( msg_start )
    {
      msg += incomming;
    }
  }
  if ( msg_valid )
  {
    msg_valid        = false;
    message_t result = StringToMessage( msg );
    return result;
  }
  else
  {
    return {0};
  }
}

message_t CanSerial::StringToMessage( String string )
{
  int       seperator = string.indexOf( ':' );
  int       id        = string.substring( 0, seperator ).toInt();
  String    message   = string.substring( seperator + 1 );
  message_t result    = {id, message};
  return result;
}

