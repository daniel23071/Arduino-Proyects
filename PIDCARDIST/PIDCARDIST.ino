#include <AFMotor.h>
AF_DCMotor motor1(2); // Front-Back motor
////////////////   Ultrasónicos 
int TRIG1 = A0; // Salida
int ECHO1 = A1; // Entrada
int t1;
int d1;
float volt, po, dist;
float vel;
//float dist_deseada = 50; // distancia deseada inicial en cm
//////////////    PID Parameters 
double Kp1 = 0.9022 , Ki1 = 0.1410 , Kd1 = 1.4436 ; 
double Setpoint1, Input1, Output1, error1;
float N = 0.0008, Ts = 0.0318; // Coeficiente de filtro y tiempo de muestreo
float U = 0, U2 = 0;
float P = 0;           
float I = 0, I_1 = 0; // Retrazos acción integral
float D = 0, D_1 = 0; // Retrazos acción derivativa
float E = 0, E_1 = 0; // Retrazos del error

//float OO = A4, O1 = A5, IO = 0, I1 = 0; // Lectura de voltaje a la salida de los motores ( realimentación )
void setup() 
{
//////////////   Ultra-sónicos

 pinMode(TRIG1, OUTPUT);
 pinMode(ECHO1, INPUT);
 Serial.begin(9600);
}
void loop() 
{

  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(TRIG1, LOW);
  
  t1 = pulseIn(ECHO1, HIGH); //obtenemos el ancho del pulso
  d1 = t1/59;             //escalamos el tiempo a una distancia en cm

  if( Serial.available() > 1) // se lee el valor de referencia de distancia
  {
        
   dist = Serial.parseFloat();
         
  
  } 
      
 if( d1 > dist)
 {
  
    Setpoint1 = (dist*200.0)/15;
  
    error1 = Setpoint1 - (d1*200.0/15);
    E =   abs(error1);
    /////////// Ecuaciones en diferencia del PID   
    P = Kp1*E;
    I = Ki1*Ts*E_1 + I_1;
    D = Kd1*N*E - Kd1*N*E_1 - ( - 1 - N*Ts)*D_1;

    U = (P + I + D);
    
    E_1 = E;
    I_1 = I;
    D_1 = D;
    // Saturador para la señal de control U
    
    if( U > 200) 
    {
      U = 200;
    }
    
    else if(U < 0)
    {
      U = 200;
    }
    
    motor1.setSpeed(U); // Se setea la velocidad del BACK-FRONT Motor
    //motor1.run(FORWARD); 
    motor1.run(BACKWARD); 
    Serial.print(millis()/1000.0,4);
    Serial.print("\t");
    Serial.print(d1);
    Serial.print("\t");
    Serial.print(Setpoint1);
    Serial.print("\t");
    Serial.print(abs(error1));
    Serial.print("\t");
    Serial.println(U);
 }
  else
 {
    Setpoint1 = (dist*200.0)/15;
    error1 = Setpoint1 - (d1*200.0/15);
    E =   abs(error1);
    /////////// Ecuaciones en diferencia del PID //
    P = Kp1*E;
    I = Ki1*Ts*E_1 + I_1;
    D = Kd1*N*E - Kd1*N*E_1 - ( - 1 - N*Ts)*D_1;
    U = (P + I + D);
    E_1 = E;
    I_1 = I;
    D_1 = D;

    // Saturador para la señal de control U
    
    if( U > 200) 
    {
      U = 200;
    }
    if (error1==0)
    {
     U=0;
    }
    
    if(U < 0)
    {
      U = 200;
    }
    
    motor1.setSpeed(U); // Se setea la velocidad del BACK-FRONT Motor
    //motor1.run(BACKWARD);
    motor1.run(FORWARD);  
    Serial.print(millis()/1000.0,4);
    Serial.print("\t");
    Serial.print(d1);
    Serial.print("\t");
    Serial.print(Setpoint1);
    Serial.print("\t");
    Serial.print(abs(error1));
    Serial.print("\t");
    Serial.println(U); 
  }

}
