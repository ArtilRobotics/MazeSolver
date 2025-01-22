#include <Arduino.h>
#include <ArtilSolver.h>

// Encoder RightEncoder(2,3);

ArtilSolver Robot;

void setup()
{
  Robot.init();
  Serial.begin(115200);
}

void loop()
{

Robot.MotorSpeed(50,-50);
Robot.IMUrotation(90);
Robot.MotorSpeed(0);
delay(3000);

}