/*
 * LaberintoSensores.cpp para robot laberinto
 * creado por Carlos Cuesta
 */

 #include "Arduino.h"
 #include "LaberintoSensores.h"

LaberintoSensores::LaberintoSensores(int RRLed[3],int RLLed[3],int ELed[3])
{
  for(int i=0; i<=2; i++){
    _RRLed[i]=RRLed[i];
  }
  for(int i=0; i<=2; i++){
    _RLLed[i]=RLLed[i];
  }
  for(int i=0; i<=2; i++){
    pinMode(ELed[i],OUTPUT);
    _ELed[i]=ELed[i];
  }
}

//lectura de sensores y devuelve un arreglo
int LaberintoSensores::RLeds()
{
  int sensores[6];
  for(int i=0; i<=2; i++){
    digitalWrite(_ELed[i],HIGH);
    sensores[i*2]=analogRead(_RRLed[i]);
    sensores[i*2+1]=analogRead(_RLLed[i]);
    delay(10);
    digitalWrite(_ELed[i],LOW);
  }
  return sensores[6];
}
