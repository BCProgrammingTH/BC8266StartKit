#include "MCP23008.h"
#include "Wire.h"

MCP23008 MCP(0x20);

long Speed = 1000;

void setup()
{
  Serial.begin(9600);
  Serial.println("BC8266 StarterKIT LED TEST");

  Wire.begin();
  MCP.begin();
  
  MCP.pinMode(4, OUTPUT);
  MCP.pinMode(5, OUTPUT);
}


void loop()
{
  MCP.digitalWrite(4, HIGH);
  MCP.digitalWrite(5, HIGH);
  delay(Speed);
  MCP.digitalWrite(4, LOW);
  MCP.digitalWrite(5, LOW);
  delay(Speed);
}
