//Library MCP23008 : https://github.com/RobTillaart/MCP23008

#include "MCP23008.h"
#include "Wire.h"

MCP23008 MCP(0x20);

boolean Status = false;
long Speed = 1000;
long Task_1;

void setup()
{
  Serial.begin(9600);
  Serial.println("BC8266 StarterKIT TestVersion");

  Wire.begin();
  MCP.begin();

  MCP.pinMode(0, OUTPUT);
  MCP.pinMode(1, OUTPUT);
  MCP.pinMode(2, OUTPUT);
  MCP.pinMode(3, OUTPUT);
  MCP.pinMode(4, OUTPUT);
  MCP.pinMode(5, OUTPUT);

  MCP.pinMode(6, INPUT);
  MCP.pinMode(7, INPUT);
}


void loop()
{

  MCP.digitalWrite(4, MCP.digitalRead(6));
  MCP.digitalWrite(5, MCP.digitalRead(7));

  if ((millis() - Task_1) >= Speed)
  {
    Task_1 = millis();

    if (Status == false)
    {
      MCP.digitalWrite(0, HIGH);
      MCP.digitalWrite(1, HIGH);
      MCP.digitalWrite(2, HIGH);
      MCP.digitalWrite(3, HIGH);
    }
    else
    {
      MCP.digitalWrite(0, LOW);
      MCP.digitalWrite(1, LOW);
      MCP.digitalWrite(2, LOW);
      MCP.digitalWrite(3, LOW);
    }
    Status = !Status;
  }
}
