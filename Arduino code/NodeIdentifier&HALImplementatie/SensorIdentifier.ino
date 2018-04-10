#include "Node.h"

#define DEBUG true

Node* node;

void setup()
{
  Serial.begin(9600);
  node = new Node();
}

void loop()
{
  Serial.println(node->GetValue());
  delay(2000);
}

