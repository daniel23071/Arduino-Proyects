const int pinecho = 11;
const int pintrigger = 12;

// VARIABLES PARA CALCULOS
unsigned int tiempo, distancia;
volatile unsigned long tiempoAnterior;
volatile double dT;

// VARIABLES DE CONTROL
double kp=30;
double ref=8;
double error=0;
double ki=0.02;
double errorSuma=0;
double kd=20;
double errorAnt=0;
double errorDer=0;
 
void setup() {
  // PREPARAR LA COMUNICACION SERIAL
  Serial.begin(4800); // CONFIGURAR PINES DE ENTRADA Y SALIDA
  pinMode(pinecho, INPUT);
  pinMode(pintrigger, OUTPUT);
  pinMode(13, OUTPUT);
  tiempoAnterior=0;
}

void loop() {

  unsigned long tiempoActual;
  tiempoActual=millis();
  dT=(double)(tiempoActual-tiempoAnterior);

  if(dT>=10){

    digitalWrite(pintrigger,HIGH);
    delayMicroseconds(2);
    digitalWrite(pintrigger,LOW);
    tiempo= pulseIn(pinecho,HIGH);
    long distancia=tiempo/58;
    distancia=27-distancia;
    error=ref-distancia;
    errorDer=error-errorAnt;
    errorSuma += (ki*error);
    double U=kp*error+(errorSuma)+kd*errorDer;
   
    if (U>255){
      U=255;
    }
    if (U<0){
      U=0;
    }
    Serial.print(ref);
    Serial.print(' ');
    Serial.println(distancia);
    analogWrite(6,floor(U));
    tiempoAnterior=tiempoActual;
  }
} 
