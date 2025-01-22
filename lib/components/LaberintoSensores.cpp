/*
 * LaberintoSensores.cpp para robot laberinto
 * creado por Carlos Cuesta
 */

#include <Arduino.h>
#include <LaberintoSensores.h>



void LaberintoSensores::init(int RRLed[3],int RLLed[3],int ELed[3])
{
  for(int i=0; i<3; i++){
    _RRLed[i]=RRLed[i];
  }
  for(int i=0; i<3; i++){
    _RLLed[i]=RLLed[i];
  }
  for(int i=0; i<3; i++){
    pinMode(ELed[i],OUTPUT);
    _ELed[i]=ELed[i];
  }
}

//lectura de sensores y devuelve un arreglo
void LaberintoSensores::RLeds(int sensores[])
{
  //int sensores[7];
  for(int i=0; i<3; i++){
    digitalWrite(_ELed[i],HIGH);
    sensores[i*2]=analogRead(_RRLed[i]);
    sensores[i*2+1]=analogRead(_RLLed[i]);
    //Serial.print(sensores[i*2]);
    //Serial.print(", ");
    //Serial.println(sensores[i*2+1]);
    delay(10);
    digitalWrite(_ELed[i],LOW);
  }
  for (int i = 0; i < 6; i++)
  {
  //Serial.print(sensores[i]);
  //Serial.print(", ");
  }
  //Serial.println();
  //Serial.println(sensores[6]);
  //return sensores[6];
}
