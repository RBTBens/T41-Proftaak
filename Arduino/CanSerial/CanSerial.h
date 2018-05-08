//
// Created by wk98 on 8-5-2018.
//

#ifndef CANSERIAL_CANSERIAL_H
#define CANSERIAL_CANSERIAL_H

#include "Arduino.h"

typedef struct
{
  int    id;
  String data;
} message_t;

class CanSerial
{
  public:
    void begin();
    void write( int8_t id, String message );
    message_t read();
  private:
    bool   msg_start;
    bool   msg_valid;
    String msg;
    message_t StringToMessage( String string );
};

#endif //CANSERIAL_CANSERIAL_H

