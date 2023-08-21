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
    void SensorsUpdate();
    int Val_Sensor(int pos_sensor);
    int IMUAngle();
    void IMUpdate();
    void Sound(int sonido);
    void Sound(int sonido,int timesound);
    void stopSound();
    float level_baterry();
    void run();
    void init();

private:
};
#endif
