#define DAC1pin 25
#define ADC0pin 36

char seleccion;
int sensor = 0;
char control = 0;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
}

void loop() {
  if(Serial.available() > 0){
      seleccion = Serial.read();
      if(seleccion == 'A')
      {
         sensor = analogRead(ADC0pin);
         Serial.write(sensor/256);
         Serial.write(sensor%256);
      };
      if(seleccion == 'D')
      {
        while(Serial.available()==0);
        control = Serial.read();
        dacWrite(DAC1pin,control);
    };
  };
}

