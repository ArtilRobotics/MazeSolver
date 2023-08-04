/*
 * LaberintoSensores.h para robot laberinto
 * creado por Carlos Cuesta
 */
#ifndef LaberintoSensores_h
#define LaberintoSensores_h

#include <Arduino.h>

class LaberintoSensores
{
  public:
    void init(int RRLed[3],int RLLed[3],int ELed[3]);
    void RLeds(int sensores[]);
    private:
    int _RRLed[3];
    int _RLLed[3];
    int _ELed[3];
    int RRLed[3];
    int RLLed[3];
    int ELed[3];
};
#endif