#include "MCP23008.h"
#include "Wire.h"

MCP23008 MCP(0x20);

void setup()
{
  Serial.begin(9600);
  Serial.println("BC8266 StarterKIT Read Button");

  Wire.begin();
  MCP.begin();

  MCP.pinMode(6, INPUT);
  MCP.pinMode(7, INPUT);
}


void loop()
{
  Serial.print("B1 : ");
  Serial.println(MCP.digitalRead(6));
  Serial.print("B2 : ");
  Serial.println(MCP.digitalRead(7));
  Serial.println();
}
