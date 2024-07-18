#include <AFMotor.h>

AF_DCMotor motor1(1); // Motor adelante-atras

const int TRIG1 = A0; 
const int ECHO1 = A1;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
}

void loop() {
  // Mover el motor hacia adelante durante 1 segundo
  motor1.setSpeed(100);
  motor1.run(FORWARD);
  delay(1000);
  
  // Detener el motor
  motor1.run(RELEASE);
  delay(2000);
  
  // Mover el motor hacia atrás durante 1 segundo
  motor1.setSpeed(150);
  motor1.run(BACKWARD);
  delay(1000);
  
  // Detener el motor
  motor1.run(RELEASE);
  delay(100);
  
  // Medir la distancia y enviar los datos a través del puerto serial cada 1 segundo
  long duration, distance;
  digitalWrite(TRIG1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  duration = pulseIn(ECHO1, HIGH);
  distance = duration / 58.2;
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
}
