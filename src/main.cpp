#include <Arduino.h>
#include <LaberintoMotor.h>
#include <LaberintoSensores.h>

//sensores infrarrojos
int RRLed[]={A4, A5, A6};     //RF RD RS 
int RLLed[]={A9, A8, A7};     //LF LD LS
int ELed[]={15, 13, 14};      //F D S
int sensores[6]; 
//Motor_Izq
#define MA 4
#define AIN1 6 
#define AIN2 5
//Motor_Der
#define MB 9
#define BIN1 7
#define BIN2 8
//Encoders
#define ED1 10
#define ED2 11 
#define EI1 2 
#define EI2 3
//varios
#define Led_rojo 27 
#define buzz 32 
#define Volt_Battery A12 

//distancias 
int cerca=900;
int medio=525;
int lejos=150;
//velocidades
int low=75;
int medium=150;
int fast = 225;

LaberintoMotor motor(MA, AIN1, AIN2, MB, BIN1, BIN2);
LaberintoSensores Distancias(RRLed, RLLed, ELed);

void recto(){
  motor.velmotor(150,150);
  delay(50);
  motor.freno(1,1);
}
void derecha(){
  motor.velmotor(150,150);
  delay(100);
  motor.freno(1,1);
  delay(10);
  motor.velmotor(150,-150);
  delay(50);
  motor.freno(1,1);
}
void izquierda(){
  motor.velmotor(150,150);
  delay(100);
  motor.freno(1,1);
  delay(10);
  motor.velmotor(-150,150);
  delay(50);
  motor.freno(1,1);
}
void mediaVuelta(){
  motor.velmotor(150,-150);
  delay(100);
  motor.freno(1,1);
}

void setup() {
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(A12,INPUT);
  Serial.println(analogRead(A12));
  
}

void loop() {
  while (analogRead(A12)<636)
  {
    digitalWrite(27,HIGH);
    //tone(buzz,104,200);
    //tone(buzz,740,200);
    //noTone(buzz);
    //Serial.println(analogRead(A12));
    
  }
    digitalWrite(27,LOW);
  Distancias.RLeds();
  /*motor.velmotor(150,150);
  delay(1000);
  motor.velmotor(0,0);
  delay(1000);
  motor.velmotor(-150,-150);
  delay(1000);
  motor.velmotor(0,0);
  delay(1000);*7
  //sensores[6]=Distancias.RLeds();
  //Serial.println(Distancias.RLeds());
  //Serial.println(analogRead(A12));
  //Serial.println(analogRead(RLLed[2]));*/

  /*digitalWrite(13,HIGH);  
  digitalWrite(14,LOW);
  digitalWrite(15,LOW);
  delay(500);

  digitalWrite(13,LOW);  
  digitalWrite(14,HIGH);
  digitalWrite(15,LOW);
  delay(500);

  digitalWrite(13,LOW);  
  digitalWrite(14,LOW);
  digitalWrite(15,LOW);
  delay(500);*/

  //  diagonal izq------------frente------------diagonal der
  /*if( sensores[3]>lejos && sensores[1]>lejos && sensores[2]>lejos ){
    derecha();
  }
  if( sensores[3]>lejos && sensores[1]>lejos && sensores[2]>medio ){
    recto();
  }
  if( sensores[3]>lejos && sensores[1]>medio && sensores[2]>lejos ){
    derecha();
  }
  if( sensores[3]>lejos && sensores[1]>medio && sensores[2]>medio ){
    izquierda();
  }
  if( sensores[3]>medio && sensores[1]>lejos && sensores[2]>lejos ){
    derecha();
  }
  if( sensores[3]>medio && sensores[1]>lejos && sensores[2]>medio ){
    recto();
  }
  if( sensores[3]>medio && sensores[1]>medio && sensores[2]>lejos ){
    derecha();
  }
  if( sensores[3]>medio && sensores[1]>medio && sensores[2]>medio ){
    mediaVuelta();
  }*/
}

