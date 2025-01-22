#include <Arduino.h>
#include <ArtilSolver.h>


//Encoder RightEncoder(2,3);

ArtilSolver Robot;

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;

void loop() {
  
  Serial.println(Robot.readLeftEncoder());

}