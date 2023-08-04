#include <Arduino.h>

#include "fis_header.h"

/*
Este es un código básico para la resolución de un laberint utilizando la regla de la mano derecha. Los valores de funcionamiento de los sensores
eben ser calibrados dependiendo los siguientes factores:
    - NIcel y condiciones de luz del lugar
    - Color de las paredes
    - Distancia entre las paredes

El automatizar este proceso ya depende de ti. Dispones de todas las herramientas necesarias para hacerlo.
*/ 

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
// int RRLed[] = {A4, A5, A6}; // RF RD RS
// int RLLed[] = {A9, A8, A7}; // LF LD LS
// int ELed[] = {30, 13, 14};  // F D S
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

int dist_right = 420;
int distancia_left = 628;
int dif_right = 0;

uint8_t turnangle;
uint8_t offset = 4;

uint8_t lastangle;
uint8_t angle;
int16_t deltaangle;

LaberintoMotor motor(MA, AIN1, AIN2, MB, BIN1, BIN2);
//LaberintoSensores Distancias(RRLed, RLLed, ELed);

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

void correccion_direccion(int velocidad)
{
    int diferencia_right;
    diferencia_right = side_right - dist_right;
    int diferencia_left;
    diferencia_left = side_left - distancia_left;

    diferencia_left = constrain(diferencia_left, -40, 40);
    diferencia_right = constrain(diferencia_right, -40, 40);

    motor.velmotor(-(velocidad + diferencia_left), -(velocidad + diferencia_right));
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

//TODO Programar una función de calibración

//TODO Crear un menú de configuración para la pantalla led

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

    // while (digitalRead(28) == 1)
    //{
    //}
    
    //TODO:Linealizar los sensores
    
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(ELed[i], HIGH);
        delay(3);
        sensores[i * 2] = analogRead(RRLed[i]);
        sensores[i * 2 + 1] = analogRead(RLLed[i]);
        // Serial.print(sensores[i*2]);
        // Serial.print(", ");
        // Serial.println(sensores[i*2+1]);
        digitalWrite(ELed[i], LOW);
        delay(5);
    }

    front_right = sensores[0];
    front_left = sensores[1];
    side_right = sensores[2];
    side_left = sensores[3];
    diagonal_right = sensores[4];
    diagonal_left = sensores[5];

    while (front_right < 900)
    {
        for (int i = 0; i < 3; i++)
        {
            digitalWrite(ELed[i], HIGH);
            delay(3);
            sensores[i * 2] = analogRead(RRLed[i]);
            sensores[i * 2 + 1] = analogRead(RLLed[i]);
            // Serial.print(sensores[i*2]);
            // Serial.print(", ");
            // Serial.println(sensores[i*2+1]);
            digitalWrite(ELed[i], LOW);
            delay(5);
        }

        front_right = sensores[0];
        front_left = sensores[1];
        side_right = sensores[2];
        side_left = sensores[3];
        diagonal_right = sensores[4];
        diagonal_left = sensores[5];
    }
    delay(2000);
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
        delay(3);
        sensores[i * 2] = analogRead(RRLed[i]);
        sensores[i * 2 + 1] = analogRead(RLLed[i]);
        // Serial.print(sensores[i*2]);
        // Serial.print(", ");
        // Serial.println(sensores[i*2+1]);
        digitalWrite(ELed[i], LOW);
        delay(5);
    }
    for (int i = 0; i < 6; i++)
    {
        Serial.print(sensores[i]);
        Serial.print(",");
    }
    Serial.println();
    // Serial.println(sensores[6]);

    front_right = sensores[0];
    front_left = sensores[1];
    side_right = sensores[2];
    side_left = sensores[3];
    diagonal_right = sensores[4];
    diagonal_left = sensores[5];

    // correccion_direccion(0);

    /*if (side_right > dist_right || side_right < dist_right)
    {
        dif_right=(side_right-dist_right);
        dif_right= constrain(dif_right,0,40);
        //motor.velmotor(-(dif_right),dif_right);
        Serial.println(dif_right);
    }*/
    
    
    if (side_right>600)
    {
        motor.velmotor(-80,80);
    }
    else if (side_left>990)
    {
        motor.velmotor(80,-80);
    }
    else if (front_right > 205 && front_left > 100 && side_right > 350 && side_left > 600)
    {
        motor.velmotor(-70, 70);
        rotation(180);
    }

    else if (front_right > 205 && front_left > 100 && side_right > 300 && side_left < 500)
    {
        motor.velmotor(20, 90);
        rotation(45);
    }

    else if (side_right < 300)
    {
        motor.velmotor(70, 20);
    }
    

    else
    {
        turnSensorUpdate();
        // Serial.print(turnAngle / turnAngle1);
        // Serial.print(", ");
        int32_t turnSpeed = -(int32_t)turnAngle / (turnAngle1 / 1.5) - turnRate / 80;
        // Serial.println(turnSpeed);
        //  Constrain our motor speeds to be between
        //  -maxSpeed and maxSpeed.
        turnSpeed = constrain(turnSpeed, -150, 150);

        motor.velmotor((100), (100));
        dif_right = 0;
        
    }

    // if (front_right > 30 && front_left > 138)
    //{
    //    motor.velmotor(0, 0);
    //}
    // motor.velmotor(40,-40);
    // rotation(90);
    // motor.velmotor(0,0);
    // delay(2000);

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
