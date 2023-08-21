#include <Arduino.h>

#include <ArtilSolver.h>
#include <U8g2lib.h>
#include <Wire.h>

ArtilSolver Maze;

// int front_right;
// int front_left;
// int side_right;
// int side_left;
// int diagonal_right;
// int diagonal_left;

int front_right;
int front_left;
int side_right;
int side_left;
int diagonal_right;
int diagonal_left;

void setup()
{
    Maze.init();
    pinMode(12, INPUT_PULLUP);
    pinMode(26, INPUT_PULLUP);
    pinMode(28, INPUT_PULLUP);
    Serial.begin(115200);

    Maze.SensorsUpdate();

    while (front_right < 900)
    {
        Maze.SensorsUpdate();
        front_right = Maze.Val_Sensor(0);
    }
    delay(2000);
}

void loop()
{

    while (Maze.level_baterry() < 6.8)
    {
        digitalWrite(27, HIGH);
        // tone(buzz,104,200);
        // tone(buzz,740,200);
        // noTone(buzz);
        // Serial.println(analogRead(A12));
    }
    digitalWrite(27, LOW);

    Maze.SensorsUpdate();

    front_right = Maze.Val_Sensor(0);
    front_left = Maze.Val_Sensor(1);
    side_right = Maze.Val_Sensor(2);
    side_left = Maze.Val_Sensor(3);
    diagonal_right = Maze.Val_Sensor(4);
    diagonal_left = Maze.Val_Sensor(5);

    Serial.print(front_right);
    Serial.print(",");
    Serial.print(front_left);
    Serial.print(",");
    Serial.print(side_right);
    Serial.print(",");
    Serial.println(side_left);

    // Serial.println(front_right);

    if (side_right < 130)
    {
        Maze.MotorSpeed(80, 20);
    }
    else if (side_left < 440)
    {
        Maze.MotorSpeed(20, 80);
    }
    else if (side_right > 600)
    {
        Maze.MotorSpeed(-80, 80);
    }
    else if (side_left > 990)
    {
        Maze.MotorSpeed(80, -80);
    }

    // else if (front_right > 205 && front_left > 100 && side_right > 350 && side_left > 600)
    // {
    //     Maze.MotorSpeed(-70, 70);
    //     Maze.IMUrotation(180);
    // }

    // else if (front_right > 205 && front_left > 100 && side_right > 300 && side_left < 500)
    // {
    //     Maze.MotorSpeed(20, 90);
    //     Maze.IMUrotation(45);
    // }

    else
    {
        // Maze.IMUpdate();
        Maze.MotorSpeed(80, 80);
    }
}