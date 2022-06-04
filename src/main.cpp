#include <LaberintoMotor.h>
#include <LaberintoSensores.h>

//sensores infrarrojos
int RRLed[]={A2, A3, A6};     //RF RD RS 
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
#define Led_amarillo 27 
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
LaberintoSensores Distancias(RRLed[3], RLLed[3], ELed[3]);

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
  
}

void loop() {
  sensores[6]=Distancias.RLeds();
  //  diagonal izq------------frente------------diagonal der
  if( sensores[3]>lejos && sensores[1]>lejos && sensores[2]>lejos ){
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
  }
}

