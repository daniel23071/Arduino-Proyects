#include <AFMotor.h>
//tiempo(T), señal cm mide sensor(E), referencia(U), salida controlador(Y)  
AF_DCMotor motor1(1); // Front-Back motor

const int TRIG1 = A0; // Salida
const int ECHO1 = A1; // Entrada
const int DISTANCIA_DESEADA = 10; // Distancia deseada en cm

// Ganancias del controlador
const float Kp = 1;
const float Kd = 0.1;
float prev_error=0;
// Variables de tiempo
unsigned long tiempo_actual, tiempo_anterior = 0;

// Variables de referencia, salida y señal de control
float referencia, salida, control_signal;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  motor1.setSpeed(255); // Establecer la velocidad del motor
}

void loop() {
  // Actualizar el tiempo
  tiempo_actual = millis();
  float dt = (tiempo_actual - tiempo_anterior) / 1000.0; // Tiempo transcurrido en segundos
  tiempo_anterior = tiempo_actual;

  // Actualizar la referencia
  referencia = DISTANCIA_DESEADA;

  // Medir la distancia
  long duration, distance;
  digitalWrite(TRIG1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  duration = pulseIn(ECHO1, HIGH);
  salida = duration * 0.034 / 2; // Convertir la duración en distancia en cm

  // Calcular la señal de control del motor
  float error = referencia - salida;
  float derivada = error - prev_error;
  prev_error = error;
  control_signal = Kp * error + Kd * derivada;

  // Controlar el motor
  if (control_signal > 0) {
    motor1.run(FORWARD);
    motor1.setSpeed(control_signal);
  } else if (control_signal < 0) {
    motor1.run(BACKWARD);
    motor1.setSpeed(-control_signal);
  } else {
    motor1.run(RELEASE);
  }

    // Mostrar las variables de tiempo, referencia, salida y señal de control en el Serial Monitor
  //Serial.print("Tiempo: ");
  Serial.print(" , ");
  Serial.print(tiempo_actual);
  //Serial.print(", Referencia: ");
  Serial.print(" , ");
  Serial.print(referencia );
  //Serial.print(", Salida: ");
  Serial.print(" , ");
  Serial.print(salida );
  //Serial.print(", Senal de control: ");
  Serial.print(" , ");
  Serial.println(control_signal );
}