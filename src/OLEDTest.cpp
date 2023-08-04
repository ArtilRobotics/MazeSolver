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

void setup()
{
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
}

void loop()
{
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
}