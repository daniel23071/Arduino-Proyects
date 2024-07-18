#include <MQ135.h>

int sensorPin = A0;
MQ135 gasSensor(sensorPin);
float sensorValue;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  delay(2000);
  sensorValue = gasSensor.getPPM();
  if(isnan(sensorValue)){
    Serial.println(F("Failed to read sensor"));
    return;
  }
  Serial.print("");
  Serial.println(sensorValue);
}