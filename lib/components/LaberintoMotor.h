/* LaberintoMotor.h - Library para Robot Laberinto
   creado por Carlos Cuesta, 27/04/2019
*/
#ifndef LaberintoMotor_h
#define LaberintoMotor_h

#include <Arduino.h>

class LaberintoMotor
{
  public:
    void init(int PWMA, int AIN1, int AIN2, int PWMB, int BIN1, int BIN2);
    void velizq(int value);
    void velder(int value);
    void velmotor(int izq, int der);
    void freno(boolean izq, boolean der);
  private:
    int _PWMA;
    int _AIN1;
    int _AIN2;
    int _PWMB;
    int _BIN1;
    int _BIN2;
};
#endif