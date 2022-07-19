#include "LaberintoMPU.h"
#include <Arduino.h>

MPU6050 mpu(Wire);

/**
 * @brief Inicializa el MPU dentro del robot, si no se inicializa no se podrá hacer uso de las otras funciones
 * 
 */
void LaberintoMPU::IMUsetup()
{
    Wire.begin();
    byte status = mpu.begin();
    Serial.print(F("MPU6050 status: "));
    Serial.println(status);
    while(status!=0){ } // stop everything if could not connect to MPU6050

    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
    mpu.calcOffsets(); // gyro and accelerometer
    Serial.println("Done!\n");
}

/**
 * @brief Permite definir un ángulo de rotación 
 * 
 * @param angulo valor de ángulo de rotación independiente del sentido 
 */
void LaberintoMPU::rotation(int16_t angulo)
{
    mpu.update();
    //Serial.println("Hola");
    turnangle=0;
    lastangle=abs(mpu.getAngleZ());
    Serial.print(turnangle);
    Serial.print(", ");
    Serial.println(lastangle);
    //Serial.print(", ");
    while (turnangle<(angulo-offset))
    {
        mpu.update();
        angle=abs(mpu.getAngleZ());
        deltaangle=angle-lastangle;
        lastangle=angle;
        turnangle+=abs(deltaangle);
        Serial.print(turnangle);
        Serial.print(", ");
        Serial.println(lastangle);
        delay(20);
  } 

}

/**
 * @brief Permite obtener la diferencia entre un ángulo inicial medido y el ángulo medido actualmente
 * 
 * @return el valor de la diferencia entre el ángulo definido y el medido
 */
int LaberintoMPU::getTurnAngle()
{
    return turnangle;
}

/**
 * @brief Permite obtener el valor del giroscopio en el eje Z
 * 
 * @return un valor numérico que presenta la variación en la velocidad 
 */
float LaberintoMPU::getturnrate()
{
    mpu.update();
    return mpu.getGyroZ();
}

/**
 * @brief Permite obtener el valor del ángulo en el eje Z
 * 
 * @return Un valor numérico que presenta el ángulo en el eje Z 
 */
float LaberintoMPU::getAccX()
{
    mpu.update();
    return mpu.getAccX();
}

float LaberintoMPU::getAccY()
{
    mpu.update();
    return mpu.getAccX();
}

float LaberintoMPU::getAccZ()
{
    mpu.update();
    return mpu.getAccX();
}

float LaberintoMPU::getGyroX()
{
    mpu.update();
    return mpu.getGyroX();
}

float LaberintoMPU::getGyroY()
{
    mpu.update();
    return mpu.getGyroY();
}

float LaberintoMPU::getGyroZ()
{
    mpu.update();
    return mpu.getGyroZ();
}

