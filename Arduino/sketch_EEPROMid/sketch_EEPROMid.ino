#include "EepromAccessor.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  EepromAccessor eepromAccessor;
  eepromAccessor.WriteID(10);
  delay(100);
  Serial.println(eepromAccessor.GetID());
}
