/* LaberintoMotor.cpp - Library para Robot Laberinto
   creado por Carlos Cuesta, 27/04/2019
*/
#include "Arduino.h"
#include "LaberintoMotor.h"

void LaberintoMotor::init(int PWMA, int AIN1, int AIN2, int PWMB, int BIN1, int BIN2)
    {
    pinMode(PWMA,OUTPUT);
    pinMode(AIN1,OUTPUT);
    pinMode(AIN2,OUTPUT);
    pinMode(PWMB,OUTPUT);
    pinMode(BIN1,OUTPUT);
    pinMode(BIN2,OUTPUT);
    _PWMA=PWMA;
    _AIN1=AIN1;
    _AIN2=AIN2;
    _PWMB=PWMB;
    _BIN1=BIN1;
    _BIN2=BIN2;
    }
    //motores velocidad izquierda
    void LaberintoMotor::velizq(int value)
    {
      if(value>=0)
      {
        digitalWrite(_AIN1,HIGH);
        digitalWrite(_AIN2,LOW);
      }
      else
      {
        digitalWrite(_AIN1,LOW);
        digitalWrite(_AIN2,HIGH);
        value*=-1;
      }
      analogWrite(_PWMA,value);
    }

    //motores velocidad derecha
    void LaberintoMotor::velder(int value)
    {
      if(value>=0)
      {
        digitalWrite(_BIN1,HIGH);
        digitalWrite(_BIN2,LOW);
      }
      else
      {
        digitalWrite(_BIN1,LOW);
        digitalWrite(_BIN2,HIGH);
        value*=-1;
      }
      analogWrite(_PWMB,value);
    }

    //velocidad motores
    void LaberintoMotor::velmotor(int izq, int der)
    {
      velizq(izq);
      velder(der);
    }

    //funcion freno
    void LaberintoMotor::freno(boolean izq, boolean der)
      {
        if(izq)
        {
          digitalWrite(_AIN1,HIGH);
          digitalWrite(_AIN2,HIGH);
        }
        if(der)
        {
          digitalWrite(_BIN1,HIGH);
          digitalWrite(_BIN2,HIGH);
        }   
      }
