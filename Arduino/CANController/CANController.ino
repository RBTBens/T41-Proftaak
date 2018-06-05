#include <CAN.h>
#include "Node.h"

#define DEBUG true
#define BIOSPHERE_ID 1
#define INTERVAL 30000

#define TEXTSIZE 7
#define DEFAULTID 0b00

Node* node;
int nodeId = BIOSPHERE_ID << 2;
unsigned long previousMillis;

// declared Variables
//  bioSphere node
//  000000000 00 = PI
//            01 = Temperature
//            10 = Light
//            11 = Soil

void WriteWithID(int id , char message[], int messageSize)
{
  if (messageSize < 8)
  {
    CAN.beginPacket(id);
    CAN.write((byte)nodeId);

    for (int i = 0; i < messageSize; i++)
    {
      CAN.write(message[i]);
    }
    CAN.endPacket();
  }
}

void onReceive(int packetSize)  // received a packet
{
  if (CAN.packetId() == nodeId)
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

      String message = "";
      // only print packet data for non-RTR packets
      while (CAN.available())
      {
        message += (char) CAN.read();
      }
      node->SetDesiredValue(message.toFloat());
      Serial.print("Received desired value: ");
      Serial.println(message);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("Serial ready");

  // Setup the CAN bus
  CAN.begin(500E3);
  CAN.onReceive(onReceive);

  // Construct node and let it identify
  node = new Node();

  // Assign ID to nodeId
  nodeId = nodeId | node->GetIdentifier();

  // Announce ID
  Serial.print("CAN Controller is ready (ID: ");
  Serial.print(nodeId);
  Serial.println(")");
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL)
  {
    previousMillis = currentMillis;

    // Check if we're not the Pi
    if (node->GetIdentifier() != DEFAULTID)
    {
      // Get current value and post that
      float result = node->GetValue();
      String temp = String(result);
      Serial.println(temp);
      char convertedString[TEXTSIZE] = { 0, };
      temp.toCharArray(convertedString, TEXTSIZE);
      WriteWithID(0, convertedString, TEXTSIZE);

      // Regulate the node for next read
      node->Regulate();
      Serial.print("My current desired value is: ");
      Serial.println(node->GetDesiredValue());
    }
  }

}

