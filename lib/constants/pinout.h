#pragma once
#include <Arduino.h>

// sensores infrarrojos
int RRLed[] = {A4, A5, A6}; // RF RD RS
int RLLed[] = {A9, A8, A7}; // LF LD LS
int ELed[] = {15, 13, 14};  // F D S
int sensores[7];
// Motor_Izq
#define MA 4
#define AIN1 5
#define AIN2 6
// Motor_Der
#define MB 9
#define BIN1 7
#define BIN2 8
// Encoders
#define ED1 10
#define ED2 11
#define EI1 2
#define EI2 3
//Botones
#define P1 12
#define P2 26
#define P3 28
// varios
#define Led_rojo 27
#define Buzzer 32
#define Volt_Battery A12

