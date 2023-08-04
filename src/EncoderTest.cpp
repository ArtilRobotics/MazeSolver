#include <Arduino.h>
#include <ArtilSolver.h>

// Encoder RightEncoder(2,3);

ArtilSolver Robot;

void setup()
{
  Serial.begin(115200);
  Serial.println("Enconder Test");
}

void loop()
{

  Serial.print("Encoder Derecho: ");
  Serial.print(Robot.readRightEncoder());
  Serial.print(", ");
  Serial.print("Encoder Izquierdo: ");
  Serial.println(Robot.readLeftEncoder());

}