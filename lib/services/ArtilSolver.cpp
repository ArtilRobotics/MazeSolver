#include <ArtilSolver.h>
#include <Arduino.h>
#include <laberintoMotor.h>
#include <LaberintoSensores.h>
#include <Encoder.h>
// #include <Wire.h>
#include <Zumo32U4IMU.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include "../constants/pinout.h"


LaberintoMotor Motores;
LaberintoSensores Sensors;
Encoder RightEncoder(ED1, ED2);
Encoder LeftEncoder(EI1, EI2);

Zumo32U4IMU imu;

#include <TurnSensor.h>

int L_Encoder;
int R_Encoder;

uint16_t turnangle;
uint16_t offset = 4;

uint32_t lastangle;
uint32_t angle;
int16_t deltaangle;

int AngleIMU;

int N_sensor;

float volt_bat;

int senso[6];

void ArtilSolver::init()
{
    Wire.setSDA(17);
    Wire.setSCL(16);
    Wire.begin();
    turnSensorSetup();
    delay(500);
    turnSensorReset();
    Motores.init(MA, AIN1, AIN2, MB, BIN1, BIN2);
    Sensors.init(RRLed, RLLed, ELed);
}

void ArtilSolver::MotorSpeed(int velizq, int velder)
{
    Motores.velmotor(velizq, velder);
}

void ArtilSolver::MotorSpeed(int velmotors)
{
    Motores.velmotor(velmotors, velmotors);
}

void ArtilSolver::moveTo(int velmotors, int position)
{
    if (readLeftEncoder() <= position && readRightEncoder() <= position)
    {
        Motores.velmotor(velmotors, velmotors);
    }
    else
    {
        Motores.velmotor(0, 0);
    }
}

int ArtilSolver::readRightEncoder()
{
    R_Encoder = RightEncoder.read();

    return R_Encoder;
}

int ArtilSolver::readLeftEncoder()
{
    L_Encoder = -1 * LeftEncoder.read();
    return L_Encoder;
}

void ArtilSolver::IMUrotation(int16_t angulo)
{
    turnSensorUpdate();
    //Serial.println("Hola");

    turnangle = 0;
    lastangle = abs(turnAngle / turnAngle1);
    Serial.print(turnangle);
    Serial.print(", ");
    Serial.println(lastangle);
    // Serial.print(", ");
    while (turnangle < (angulo - offset))
    {
        turnSensorUpdate();
        angle = abs(turnAngle / turnAngle1);
        deltaangle = angle - lastangle;
        lastangle = angle;
        turnangle += abs(deltaangle);
        Serial.print(turnangle);
        Serial.print(", ");
        Serial.println(lastangle);
        delay(20);
    }
}

void ArtilSolver::SensorsUpdate()
{
    Sensors.RLeds(senso);
    //return senso;
}



int ArtilSolver::Val_Sensor(int pos_sensor)
{
int valor_sensor=senso[pos_sensor];
return valor_sensor;
}


int ArtilSolver::IMUAngle()
{
    turnSensorUpdate();
    lastangle = abs(turnAngle / turnAngle1);
    return lastangle;
}

void ArtilSolver::IMUpdate()
{
    turnSensorUpdate();
}

void ArtilSolver::Sound(int sonido)
{
    tone(Buzzer,sonido);
}

void ArtilSolver::Sound(int sonido,int timesound)
{
    tone(Buzzer,sonido,timesound);
}

void ArtilSolver::stopSound()
{
    noTone(Buzzer);
}

float ArtilSolver::level_baterry()
{
    volt_bat=analogRead(Volt_Battery);
    volt_bat=volt_bat/100;
    return volt_bat;
}
