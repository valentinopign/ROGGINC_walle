
#define RIGHT 18 
#define RIGHT2 23 


#define LEFT 19  
#define LEFT2 4 


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pca9685;

#include "BluetoothSerial.h"
BluetoothSerial BT;

#define SERVO1_PIN_L 0 // Canal del PCA9685 para el primer servo
#define SERVO2_PIN_R 1
#define SERVO3_PIN_H 2
#define SERVO4_PIN_N 3



int grad = 0;


void Stop();
void forward();
void back();
void left();
void right();
void topright();
void topleft();
void bottomright();
void bottomleft();

#define SERVOMIN 150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 220 // ) //cambiar / subir para dejar al servo moverse mas //o puede ser USMAX
#define USMIN 150 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 600 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


void setup(){
  
  
    pinMode(RIGHT, OUTPUT);
    pinMode(RIGHT2, OUTPUT);
    pinMode(LEFT, OUTPUT);
    pinMode(LEFT2, OUTPUT);


    pca9685.begin();
    pca9685.setOscillatorFrequency(27000000);
    pca9685.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates; // Establecer la frecuencia PWM en 60 Hz

    // Configura la posición inicial de los servos
    pca9685.setPWM(SERVO1_PIN_L, 0, 4095); // Coloca el servo 1 en la posición inicial
    pca9685.setPWM(SERVO2_PIN_R, 0, 4095);
    
    Serial.begin(115200);
    BT.begin("rodvert");
}


void loop(){
  if (BT.available()) {
    int read = BT.read();
    //while 
   
     listenBluetoothCommands(read);
      listenServosCommands(read);
  }else{
    Stop();
  }
  delay(10);
}

void listenBluetoothCommands(int val){
  if (val == 'F'){
    forward();
    Serial.println("F");
  }

  if (val == 'G'){
    back();
    Serial.println("G");

  }

  if (val == 'L'){
    left();
    Serial.println("L");
  }

  if (val == 'R'){
    Serial.println("R");
      right();
  }
  if (val == 'Q'){
    Serial.println("Q");
   topright();
  }

  if (val == 'E'){
    Serial.println("E");

    topleft();
  }

  if (val == 'Z'){
    Serial.println("Z");
    bottomright();
  }

  if (val == 'C'){
    Serial.println("C");
    bottomleft();
  }

  if (val == 'S'){ //sin comillas
    Stop(); 
  }
}
  

void listenServosCommands(int val){
  Serial.println("Val is");
  Serial.println(val);
  
  if (val == 89){ 
      while(true){ //dangereous
        Serial.println("up & down left");
        for (int i = 0; i < 270;i++){
          moveServo(SERVO1_PIN_L,i);
          delay(10);
          Serial.println("up");
        }
        delay(1000);
        for (int i = 270; i >= 0;i--){
          moveServo(SERVO1_PIN_L,i);
          delay(10);
          Serial.println(" downt");
        }
        Serial.println("finish down and up ");
        break;
      }
    }
      if (val == 88){ //change later
      while(true){ //dangereous
        Serial.println("up & down left");
        for (int i = 0; i < 180;i++){
          moveServo(SERVO2_PIN_R,i);
          delay(10);
          Serial.println("up");
        }
        delay(1000);
        for (int i = 180; i >= 0;i--){
          moveServo(SERVO2_PIN_R,i);
          delay(10);
          Serial.println(" downt");
        }
        Serial.println("finish down up :v uwu");
        break;
      }
    }
      if (val == 77){ //CUELLITOp
      while(true){ //dangereous
        Serial.println("up and down neckbottom");
        for (int i = 0; i < 360;i++){
          moveServo(SERVO3_PIN_H,i);
          delay(10);
          Serial.println("upp");
        }
        delay(1000);
        for (int i = 360; i >= 0;i--){
          moveServo(SERVO3_PIN_H,i);
          delay(10);
          Serial.println(" downtt");
        }
        Serial.println("finish down up :v uwu");
        break;
      }
    }
      if (val == 78){ //CABEZA
      while(true){ //dangereous
        Serial.println("up & down necktop");
        for (int i = 0; i < 400;i++){
          moveServo(SERVO4_PIN_N,i);
          delay(10);
          Serial.println("upi");
        }
        delay(1000);
        for (int i = 400; i >= 0;i--){
          moveServo(SERVO4_PIN_N,i);
          delay(10);
          Serial.println(" downti");
        }
        Serial.println("finish down up :v uwu");
        break;
      }
    }
    
}

void moveServo(uint8_t servoPin, int degrees) {
  uint8_t pulselength = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
  pca9685.setPWM(servoPin, 0, pulselength); // Establecer la posición del servo
}

void forward()
{
 digitalWrite(RIGHT, HIGH);
  digitalWrite(RIGHT2, LOW);
 

  digitalWrite(LEFT, HIGH);
  digitalWrite(LEFT2, LOW);
  
}
   
void back()
{
  digitalWrite(RIGHT, LOW);
  digitalWrite(RIGHT2, HIGH);
  

  digitalWrite(LEFT, LOW);
  digitalWrite(LEFT2, HIGH);
  
}
   
void left()
{
 
  digitalWrite(RIGHT, HIGH);
  digitalWrite(RIGHT2, LOW);
  

  digitalWrite(LEFT, LOW);
  digitalWrite(LEFT2, HIGH);
  
 
   
}
   
void right()
{
 
  digitalWrite(RIGHT, LOW);
  digitalWrite(RIGHT2, HIGH);
 

  digitalWrite(LEFT, HIGH);
  digitalWrite(LEFT2, LOW);
  
   
}
   
void topleft(){
 
    digitalWrite(RIGHT, HIGH);
  digitalWrite(RIGHT2, LOW);
 

  digitalWrite(LEFT, LOW);
  digitalWrite(LEFT2, LOW);
  
 
}
   
void topright()
{
  
    digitalWrite(RIGHT, LOW);
  digitalWrite(RIGHT2, LOW);
 

  digitalWrite(LEFT, HIGH);
  digitalWrite(LEFT2, LOW);
  

 

   
}
   
void bottomleft()
{
 
  digitalWrite(RIGHT, LOW);
  digitalWrite(RIGHT2, LOW);
  

  digitalWrite(LEFT, LOW);
  digitalWrite(LEFT2, HIGH);
  

 
   
}
   
void bottomright()
{
 
 
 
  digitalWrite(RIGHT, LOW);
  digitalWrite(RIGHT2, HIGH);
 

  digitalWrite(LEFT, LOW);
  digitalWrite(LEFT2, LOW);
  
   
 
}
   
   
void Stop()
{
  digitalWrite(RIGHT, LOW);
  digitalWrite(RIGHT2, LOW);
 

  digitalWrite(LEFT, LOW);
  digitalWrite(LEFT2, LOW);
  
}
