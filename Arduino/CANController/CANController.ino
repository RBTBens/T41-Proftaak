#include <CAN.h>
#include "Node.h"

#define NodeID 0b00000000111
#define DEBUG true

Node* node;

// declared Variables
//  bioSphere node
//  000000000 00 = PI
//            01 = Temperature
//            10 = Light
//            11 = Water

void WriteWithID(int id , char message[], int messageSize)
{
  if (messageSize < 9)
  {
    CAN.beginPacket(id);
    for (int i = 0; i < messageSize; i++)
    {
      CAN.write(message[i]);
    }
    CAN.endPacket();
  }
}

void onReceive(int packetSize)  // received a packet
{
  if (CAN.packetId() == NodeID)
  {
    Serial.print("Received ");

    if (CAN.packetExtended())
    {
      Serial.print("extended ");
    }

    if (CAN.packetRtr())
    {
      // Remote transmission request, packet contains no data
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    if (CAN.packetRtr())
    {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);

      // only print packet data for non-RTR packets
      while (CAN.available())
      {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }

    Serial.println();
  }
}

void setup()
{
  Serial.begin(115200);
  CAN.begin(500E3);
  CAN.onReceive(onReceive); // register the receive callback

  node = new Node();
}

void loop()
{
  String stringetje = "tekst";
  int textSize = stringetje.length() + 1;

  // TODO: Check textSize length to be 8 at max

  char convertedString[textSize];
  stringetje.toCharArray(convertedString, textSize);

  WriteWithID(5, convertedString, textSize);

  // Serial.println(node->GetValue());
}

