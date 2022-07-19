#include <Arduino.h>

#include "fis_header.h"

// Number of inputs to the fuzzy inference system
const int fis_gcI = 4;
// Number of outputs to the fuzzy inference system
const int fis_gcO = 2;
// Number of rules to the fuzzy inference system
const int fis_gcR = 77;

FIS_TYPE g_fisInput[fis_gcI];
FIS_TYPE g_fisOutput[fis_gcO];

#include <LaberintoMotor.h>
#include <LaberintoSensores.h>
#include <Wire.h>
#include <Zumo32U4IMU.h>

Zumo32U4IMU imu;

#include <TurnSensor.h>

// sensores infrarrojos
int RRLed[] = {A4, A5, A6}; // RF RD RS
int RLLed[] = {A9, A8, A7}; // LF LD LS
int ELed[] = {30, 13, 14};  // F D S
int sensores[7];
// Motor_Izq
#define MA 4
#define AIN1 6
#define AIN2 5
// Motor_Der
#define MB 9
#define BIN1 7
#define BIN2 8
// Encoders
#define ED1 10
#define ED2 11
#define EI1 2
#define EI2 3
// varios
#define Led_rojo 27
#define buzz 32
#define Volt_Battery A12

// distancias
int cerca = 900;
int medio = 525;
int lejos = 150;
// velocidades
int low = 75;
int medium = 150;
int fast = 225;

int _sensor[7];
int front_right = 0;
int front_left = 0;
int side_right = 0;
int side_left = 0;
int diagonal_right = 0;
int diagonal_left = 0;

int distancia_right = 0;
int distancia_left = 0;

uint8_t turnangle;
uint8_t offset = 4;

uint8_t lastangle;
uint8_t angle;
int16_t deltaangle;

LaberintoMotor motor(MA, AIN1, AIN2, MB, BIN1, BIN2);
LaberintoSensores Distancias(RRLed, RLLed, ELed);

void recto()
{
    motor.velmotor(150, 150);
    delay(50);
    motor.freno(1, 1);
}
void derecha()
{
    motor.velmotor(150, 150);
    delay(100);
    motor.freno(1, 1);
    delay(10);
    motor.velmotor(150, -150);
    delay(50);
    motor.freno(1, 1);
}
void izquierda()
{
    motor.velmotor(150, 150);
    delay(100);
    motor.freno(1, 1);
    delay(10);
    motor.velmotor(-150, 150);
    delay(50);
    motor.freno(1, 1);
}
void mediaVuelta()
{
    motor.velmotor(150, -150);
    delay(100);
    motor.freno(1, 1);
}

void correccion_direccion(int velocidad, int divisor_comp)
{
    int diferencia_right;
    diferencia_right = side_right - distancia_right;
    int diferencia_left;
    diferencia_left = side_left - distancia_left;
    motor.velmotor(velocidad + (diferencia_left / divisor_comp), velocidad + (diferencia_right / divisor_comp));
}

void rotation(int16_t angulo)
{
    turnSensorUpdate();
    // Serial.println("Hola");

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

void setup()
{
    pinMode(13, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(A12, INPUT);
    // Boton P3
    pinMode(28, INPUT_PULLUP);

    Serial1.begin(9600);

    Wire.setSCL(16);
    Wire.setSDA(17);
    Wire.begin();
    turnSensorSetup();
    delay(500);
    turnSensorReset();
    while (digitalRead(28) == 1)
    {
    }
}

// Loop routine runs over and over again forever:
void loop()
{

    while (analogRead(A12) < 636)
    {
        digitalWrite(27, HIGH);
        // tone(buzz,104,200);
        // tone(buzz,740,200);
        // noTone(buzz);
        // Serial.println(analogRead(A12));
    }
    digitalWrite(27, LOW);

    for (int i = 0; i < 3; i++)
    {
        digitalWrite(ELed[i], HIGH);
        sensores[i * 2] = analogRead(RRLed[i]);
        sensores[i * 2 + 1] = analogRead(RLLed[i]);
        // Serial.print(sensores[i*2]);
        // Serial.print(", ");
        // Serial.println(sensores[i*2+1]);
        delay(10);
        digitalWrite(ELed[i], LOW);
    }
    for (int i = 0; i < 6; i++)
    {
        Serial.print(sensores[i]);
        Serial.print(", ");
    }
    Serial.println();
    // Serial.println(sensores[6]);

    front_right = sensores[0];
    front_left = sensores[1];
    side_right = sensores[2];
    side_left = sensores[3];
    diagonal_right = sensores[4];
    diagonal_left = sensores[5];

    turnSensorUpdate();
    //Serial.print(turnAngle / turnAngle1);
    //Serial.print(", ");
    int32_t turnSpeed = -(int32_t)turnAngle / (turnAngle1 / 1.5) - turnRate / 80;
    //Serial.println(turnSpeed);
    // Constrain our motor speeds to be between
    // -maxSpeed and maxSpeed.
    turnSpeed = constrain(turnSpeed, -150, 150);


    //motor.velmotor(70+turnSpeed, 70-turnSpeed);
    if(front_right>30 && front_left>305)
    {
        motor.velmotor(0,0);
    }
    //motor.velmotor(40,-40);
    //rotation(90);
    //motor.velmotor(0,0);
    //delay(2000);

    // velmotor(izquierdo,derecho)

    /*if (side_right < 100)
    {
        motor.velmotor(100, 50);
        // MPU.rotation(90);//Cambiar por la otra IMU
    }
    else if (side_right > 100 && front_right < 100 && front_left > 100 && side_left > 100)
    {
        motor.velmotor(-100, 100);
        // MPU.rotation(180);//Cambiar por la otra IMU
    }
    else if (side_right > 100 && front_right < 100 && front_left > 100 && side_left < 100)
    {
        motor.velmotor(50, 100);
        // MPU.rotation(90);//Cambiar por la otra IMU
    }
    else if (front_left > 427 || front_right > 80)
    {
        motor.velmotor(0, 0);
    }
    else
    {
        correccion_direccion(100, 2);
    }*/
}
