#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define POT1_PIN 34
#define POT2_PIN 35
#define TIME_TO_SLEEP 1
static int counter;
static SemaphoreHandle_t xSemaphore;
static SemaphoreHandle_t mutexADC;
static SemaphoreHandle_t mutex1;
static SemaphoreHandle_t mutex2;
static SemaphoreHandle_t mutexSerial;

int port1 = 0,port2 = 0;

void Task1code( void * parameter) {
  int myCounter;
  //double arreglo[10000];
  while(1){
    xSemaphoreTake(mutexSerial,portMAX_DELAY);
    myCounter=counter;
    
    Serial.print("Task running on core ");
    Serial.println(xPortGetCoreID());
    //   Serial.print(" and counter value is: ");
    // Serial.println(myCounter);
    xSemaphoreTake(mutex1,portMAX_DELAY);
    Serial.println(port1);
    Serial.flush();
    xSemaphoreGive(mutex1);
    xSemaphoreGive(mutexSerial);

     xSemaphoreTake(mutex2,portMAX_DELAY);
    xSemaphoreTake(mutexADC,portMAX_DELAY);    
    port2 = analogRead(POT2_PIN);
    xSemaphoreGive(mutexADC);    
    xSemaphoreGive(mutex2);
    xSemaphoreTake(xSemaphore, portMAX_DELAY);

    //vTaskDelay(1500/portTICK_PERIOD_MS);
  }
  }

void Task2code( void * parameter) {
  while(1){
    xSemaphoreTake(mutexSerial,portMAX_DELAY);
    Serial.print("Task running on core ");
    Serial.println(xPortGetCoreID());
    xSemaphoreTake(mutex2,portMAX_DELAY);
    Serial.println(port2);
    counter++;
    xSemaphoreGive(mutex2);
    Serial.flush();
    xSemaphoreGive(mutexSerial);

      xSemaphoreTake(mutex1,portMAX_DELAY);
    xSemaphoreTake(mutexADC,portMAX_DELAY);    
    port1 = analogRead(POT1_PIN);
    xSemaphoreGive(mutexADC);    
    xSemaphoreGive(mutex1);

  

   // vTaskDelay(1500/portTICK_PERIOD_MS);

    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * 1000000);
    esp_light_sleep_start();
    xSemaphoreGive(xSemaphore);
    // mutex=xSemaphoreCreateBinary();
    //if(mutex==NULL){
     // esp_deep_sleep_star();
    //}//else{
      
    //}
  }
  }
void setup() {
   TaskHandle_t Task1,Task2;
   Serial.begin(115200);
   pinMode(POT1_PIN,OUTPUT); 
   pinMode(POT2_PIN,OUTPUT); 
   pinMode(2,OUTPUT);
      digitalWrite(2,1);
      delay(1000);
   Serial.print("setup() running on core ");
   Serial.println(xPortGetCoreID());
   counter=0;
  mutexADC = xSemaphoreCreateMutex();
  mutex1 = xSemaphoreCreateMutex();
  mutex2 = xSemaphoreCreateMutex();
  mutexSerial = xSemaphoreCreateMutex();
  xSemaphore = xSemaphoreCreateBinary();

  xTaskCreatePinnedToCore(
      Task1code, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      10,  /* Priority of the task */
      &Task1,  /* Task handle. */
      1); /* Core where the task should run */

  xTaskCreatePinnedToCore(
      Task2code, /* Function to implement the task */
      "Task2", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      10,  /* Priority of the task */
      &Task2,  /* Task handle. */
      0); /* Core where the task should run */
}


void loop() {
  // nothing to do here
  vTaskDelete(NULL);
}
