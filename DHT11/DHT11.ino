#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 3
#define DHTTYPE DHT11

DHT dht11(DHTPIN,DHTTYPE);
float temp, hum;
void setup() 
{
  Serial.begin(9600);
  pinMode(DHTPIN, INPUT);
  dht11.begin();
  
}

void loop() 
{
  delay(2000);
  temp = dht11.readTemperature();
  hum = dht11.readHumidity();

  if(isnan(hum)||isnan(temp)){
    Serial.println(F("Failed to Read"));
    return;
  }

  Serial.print((int)temp); 
  Serial.print(","); 
  Serial.print((int)hum);
 
}
