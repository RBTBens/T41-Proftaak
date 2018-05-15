//
// Created by wk98 on 8-5-2018.
//

#include "CanSerial.h"

void CanSerial::begin()
{
    Serial.begin( 115200 );
    msg_start = false;
    msg_valid = false;
    msg       = "";
}

void CanSerial::write( message_t message )
{
    if ( message.messageSize < 9 )
    {
        String msg = "#";
        msg += message.id;
        msg += ":";
        for ( int i = 0; i < message.messageSize; i++ )
        {
            msg += message.message[i];
        }
        msg += ";";
        Serial.print( msg );
    }
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
    message_t result    = {0};
    int       seperator = string.indexOf( ':' );
    if ( seperator > 0 )
    {
        int    id      = string.substring( 0, seperator ).toInt();
        String message = string.substring( seperator + 1 );
        result.id = id;
        for ( int i = 0; i < message.length(); i++ )
        {
            result.message[i] = message[i];
        }
        result.messageSize = message.length();
    }
    return result;
}

