#pragma once

#ifndef ArtilSolver_h
#define ArtilSolver_h

#include <stdint.h>

class ArtilSolver
{
public:
    void MotorSpeed(int velizq, int velder);
    void MotorSpeed(int velmotors);
    void moveTo(int velmotors,int position);
    int readLeftEncoder();
    int readRightEncoder();
    void IMUrotation(int16_t angulo);
    int Sens();
    int IMUAngle();

    void run();
    void init();

private:
};
#endif
