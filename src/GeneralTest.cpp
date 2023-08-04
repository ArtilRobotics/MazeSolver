#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArtilSolver.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

ArtilSolver Robot;

int botonState = 0;
int botonState2 = 0;
int botonState3 = 0;

void setup()
{
    Robot.init();
    Wire.setSDA(17);
    Wire.setSCL(16);
    Wire.begin();
    Serial.begin(115200);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
    delay(2000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("Enconder Izquierdo:");
    display.setCursor(0, 20);
    // Display static text
    display.println("Encoder Derecho: ");
    display.display();

    pinMode(12, INPUT_PULLUP);
    pinMode(26, INPUT_PULLUP);
    pinMode(28, INPUT_PULLUP);
}

void loop()
{
    if (digitalRead(28) == 0)
    {
        // el operador % significa modulo
        botonState = (botonState + 1) % 3;
        delay(200);
    }
    switch (botonState)
    {
    case 2:
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(10, 5);
        display.println("IMU");

        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 30);
        display.println("Angulo IMU:");
        display.setCursor(80, 30);
        display.println(Robot.IMUAngle());
        display.display();
        break;
    case 1:
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(10, 5);
        display.println("ENCONDERS");

        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 30);
        display.println("Enconder Izq:");
        display.setCursor(0, 40);
        display.println("Encoder Der: ");
        display.setCursor(80, 30);
        display.println(Robot.readLeftEncoder());
        display.setCursor(80, 40);
        display.println(Robot.readRightEncoder());
        display.display();
        break;
    case 0:
        // display.clearDisplay();
        // display.setTextSize(2);
        // display.setTextColor(WHITE);
        // display.setCursor(10, 5);
        // display.println("Sensores");

        // display.setTextSize(1);
        // display.setTextColor(WHITE);
        // display.setCursor(0, 30);
        // display.println("Sensor Der: ");
        // display.setCursor(0, 40);
        // display.println("Encoder Izqu: ");
        // display.setCursor(80, 30);
        // //display.println(Robot.Sens());
        // display.setCursor(80, 40);
        // //display.println(Robot.Sens());

        // display.display();
        display.clearDisplay();
        display.setTextSize(3);
        display.setTextColor(WHITE);
        display.setCursor(20, 10);
        display.println("Artil");
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(25, 40);
        display.println("Solver");
        display.display();
        break;
    }

    if (digitalRead(12) == 0)
    {
        // el operador % significa modulo
        botonState2 = (botonState2 + 1) % 3;
        delay(200);
    }
    switch (botonState2)
    {
    case 0:
        Robot.MotorSpeed(0, 0);
        break;
    case 1:
        Robot.MotorSpeed(50, 0);
        break;
    }

    if (digitalRead(26) == 0)
    {
        // el operador % significa modulo
        botonState3 = (botonState3 + 1) % 3;
        delay(200);
    }
    switch (botonState3)
    {
    case 0:
        Robot.MotorSpeed(0, 0);
        break;
    case 1:
        Robot.MotorSpeed(0, 50);
        break;
    }
}
