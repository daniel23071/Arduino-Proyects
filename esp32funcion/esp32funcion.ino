#define ADC0pin 36
#define DAC1pin 25
#define Tm 100

volatile int interruptCounter;
void IRAM_ATTR onTimer(){
  interruptCounter++;
}

hw_timer_t * timer = NULL;
void setup (){
Serial.begin(115200);
timer = timerBegin (0, 8000, true);
timerAttachInterrupt(timer, &onTimer, true);
timerAlarmWrite(timer, 10*Tm, true);
timerAlarmEnable(timer);
}
const float b0=0, b1= 0.009630939969927 , b2=-0.009411228688830;
const float a1=-1.984501856576887 , a2=0.984733138399232;

float U = 0 , U_1=0, U_2=0;
float Y= 0 , Y_1=0, Y_2=0;

void loop(){
if (interruptCounter > 0) {
  interruptCounter--;
  U = analogRead (ADC0pin)*3.2/4095.0;
  Y = b0*U+b1*U_1+b2*U_2-a1*Y_1-a2*Y_2;
  U_2=U_1;
  U_1=U;
  Y_2=Y_1;
  Y_1=Y;
  if (Y<0) Y=0;
  if (Y>3.2) Y=3.2;
  dacWrite(DAC1pin,Y*255/3.2);
  Serial.print(U);
  Serial.print(",");
  Serial.println(Y);

}
}
