#include "CanSerial.h"

CanSerial serial;

void setup() {
  serial.begin();
}

void loop() {
  message_t receivedMessage = serial.read();
  if (receivedMessage.id > 0) {
    // Message complete, do stuff
    // Echo message
    serial.write(receivedMessage.id, receivedMessage.data);
  }
}
