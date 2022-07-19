#pragma once

#ifndef LaberintoMPU_h
#define LaberintoMPU_h

#include <Arduino.h>
#include <MPU6050_light.h>



class LaberintoMPU
{
    public:
        void rotation(int16_t angulo);
        int getTurnAngle();
        float getturnrate();
        float getZ_angle();
        float getAccX();
        float getAccY();
        float getAccZ();
        float getGyroX();
        float getGyroY();
        float getGyroZ();

        void IMUsetup();
        uint8_t turnangle;
        uint8_t offset=8.5;

    private:
        uint8_t lastangle;
        uint8_t angle;
        int16_t deltaangle;
       

}; 

#endif