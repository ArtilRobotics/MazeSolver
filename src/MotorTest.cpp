#include <Arduino.h>
#include <ArtilSolver.h>
#include <LaberintoMotor.h>
#include "../constants/pinout.h"

LaberintoMotor Motor;
void setup() {

Motor.init(MA, AIN1, AIN2, MB, BIN1, BIN2);

}



void loop() 
{

Motor.velmotor(0,0);

}
