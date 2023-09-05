#include <Arduino.h>
#include <ArtilSolver.h>
#include <U8g2lib.h>
#include "../constants/xbmimages.h"
#include "../constants/notes.h"
#include <Wire.h>

ArtilSolver Robot;

// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/16, /* data=*/17, /* reset=*/U8X8_PIN_NONE); // All Boards without Reset of the Display

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

// 'Menu1', 128x64px
// ' ledicon', 16x16px

void gameofthronessong()
{

    for (int i = 0; i < 4; i++)
    {
        Robot.Sound(NOTE_G4);
        delay(500);
        Robot.stopSound();
        Robot.Sound(NOTE_C4);
        delay(500);
        Robot.stopSound();
        Robot.Sound(NOTE_DS4);
        delay(250);
        Robot.stopSound();
        Robot.Sound(NOTE_F4);
        delay(250);
        Robot.stopSound();
    }
    for (int i = 0; i < 4; i++)
    {
        Robot.Sound(NOTE_G4);
        delay(500);
        Robot.stopSound();
        Robot.Sound(NOTE_C4);
        delay(500);
        Robot.stopSound();
        Robot.Sound(NOTE_E4);
        delay(250);
        Robot.stopSound();
        Robot.Sound(NOTE_F4);
        delay(250);
        Robot.stopSound();
    }
    Robot.Sound(NOTE_G4);
    delay(500);
    Robot.stopSound();
    Robot.Sound(NOTE_C4);
    delay(500);
    Robot.Sound(NOTE_DS4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_F4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_D4);
    delay(500);
    Robot.stopSound();
    for (int i = 0; i < 3; i++)
    {
        Robot.Sound(NOTE_G3);
        delay(500);
        Robot.stopSound();
        Robot.Sound(NOTE_AS3);
        delay(250);
        Robot.stopSound();
        Robot.Sound(NOTE_C4);
        delay(250);
        Robot.stopSound();
        Robot.Sound(NOTE_D4);
        delay(500);
        Robot.stopSound();
    } //
    Robot.Sound(NOTE_G3);
    delay(500);
    Robot.stopSound();
    Robot.Sound(NOTE_AS3);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_C4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_D4);
    delay(1000);
    Robot.stopSound();

    Robot.Sound(NOTE_F4);
    delay(1000);
    Robot.stopSound();
    Robot.Sound(NOTE_AS3);
    delay(1000);
    Robot.stopSound();
    Robot.Sound(NOTE_DS4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_D4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_F4);
    delay(1000);
    Robot.stopSound();
    Robot.Sound(NOTE_AS3);
    delay(1000);
    Robot.stopSound();
    Robot.Sound(NOTE_DS4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_D4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_C4);
    delay(500);
    Robot.stopSound();
    for (int i = 0; i < 3; i++)
    {
        Robot.Sound(NOTE_GS3);
        delay(250);
        Robot.stopSound();
        Robot.Sound(NOTE_AS3);
        delay(250);
        Robot.stopSound();
        Robot.Sound(NOTE_C4);
        delay(500);
        Robot.stopSound();
        Robot.Sound(NOTE_F3);
        delay(500);
        Robot.stopSound();
    }
    Robot.Sound(NOTE_G4);
    delay(1000);
    Robot.stopSound();
    Robot.Sound(NOTE_C4);
    delay(1000);
    Robot.stopSound();
    Robot.Sound(NOTE_DS4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_F4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_G4);
    delay(1000);
    Robot.stopSound();
    Robot.Sound(NOTE_C4);
    delay(1000);
    Robot.stopSound();
    Robot.Sound(NOTE_DS4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_F4);
    delay(250);
    Robot.stopSound();
    Robot.Sound(NOTE_D4);
    delay(500);
    Robot.stopSound();
    for (int i = 0; i < 4; i++)
    {
        Robot.Sound(NOTE_G3);
        delay(500);
        Robot.stopSound();
        Robot.Sound(NOTE_AS3);
        delay(250);
        Robot.stopSound();
        Robot.Sound(NOTE_C4);
        delay(250);
        Robot.stopSound();
        Robot.Sound(NOTE_D4);
        delay(500);
        Robot.stopSound();
    }
}

int opcion_seleccionada = 0;
int opcion_anterior;
int opcion_siguiente;

int prev_encoderiz = 0;
int prev_encoderder = 0;
int actual_encoderiz;
int actual_encoderder;

int botonState = 0;
int botonState2 = 0;
int botonState3 = 0;

int lvl_baterry = 0;
int porcen_baterry = 0;

char Enco_Der[5];
char Enco_Iz[5];
char Dato_IMU[5];
char Sensor_FD[5];
char Sensor_FI[5];
char Sensor_LD[5];
char Sensor_LI[5];
char Bateria_lvl[4];

bool menuflag = false;

int botonDer_Submenu = 0;
int botonIz_Submenu = 0;
int bot_iz_alte = 0;

int submenu = 0;

int soundIMU;

void setup(void)
{
    Robot.init();
    u8g2.begin();
    pinMode(12, INPUT_PULLUP);
    pinMode(26, INPUT_PULLUP);
    pinMode(28, INPUT_PULLUP);
    Serial.begin(115200);
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g_font_7x14); // choose a suitable font
    u8g2.drawXBMP(10, 10, 108, 44, logo_artil);
    u8g2.sendBuffer();
    delay(3000);
}

void loop(void)
{

    Serial.println(Robot.IMUAngle());
    if (menuflag == false)
    {

        if (digitalRead(12) == LOW)
        {
            Robot.Sound(440, 50);
            opcion_seleccionada = opcion_seleccionada - 1;
            if (opcion_seleccionada < 0)
            {
                opcion_seleccionada = NUM_ITEMS - 1;
            }
            delay(200);
        }

        if (digitalRead(28) == LOW)
        {
            Robot.Sound(330, 50);
            opcion_seleccionada = opcion_seleccionada + 1;
            if (opcion_seleccionada >= 7)
            {
                opcion_seleccionada = 0;
            }
            delay(200);
        }
    }

    opcion_anterior = opcion_seleccionada - 1;
    if (opcion_anterior < 0)
    {
        opcion_anterior = NUM_ITEMS - 1;
    }
    opcion_siguiente = opcion_seleccionada + 1;
    if (opcion_siguiente >= NUM_ITEMS)
    {
        opcion_siguiente = 0;
    }

    if (submenu == 4 && menuflag == true)
    {
        if (digitalRead(12) == LOW)
        {
            Robot.Sound(440);
            // el operador % significa modulo
            Robot.MotorSpeed(200, 0);
        }
        else if (digitalRead(28) == LOW)
        {
            Robot.Sound(261);
            // el operador % significa modulo
            Robot.MotorSpeed(0, 200);
        }
        else{

            Robot.MotorSpeed(0,0);
            Robot.stopSound();

        }
        
        // else
        // {
        //     Robot.MotorSpeed(0, 0);
        //     Robot.stopSound();
        // }
    }

    if (digitalRead(26) == 0)
    {
        Robot.Sound(261, 50);
        // el operador % significa modulo
        botonState2 = (botonState2 + 1) % 2;
        delay(200);
    }
    switch (botonState2)
    {
    case 0:
        u8g2.clearBuffer();          // clear the internal memory
        u8g2.setFont(u8g_font_7x14); // choose a suitable font
        u8g2.drawXBMP(0, 22, 128, 23, epd_bitmap__selector);
        u8g2.drawXBMP(120, 0, 8, 64, epd_bitmap__scrollbar);
        u8g2.drawXBMP(4, 2, 16, 16, icons[opcion_anterior]);
        u8g2.drawXBMP(4, 24, 16, 16, icons[opcion_seleccionada]);
        u8g2.drawXBMP(4, 46, 16, 16, icons[opcion_siguiente]);
        u8g2.setFont(u8g_font_7x14);
        u8g2.drawStr(26, 15, menu_opciones[opcion_anterior]);
        u8g2.setFont(u8g_font_7x14B);
        u8g2.drawStr(26, 37, menu_opciones[opcion_seleccionada]);
        u8g2.setFont(u8g_font_7x14);
        u8g2.drawStr(26, 59, menu_opciones[opcion_siguiente]);
        u8g2.sendBuffer(); // transfer internal memory to the display
        menuflag = false;
        submenu = 0;

        break;
    case 1:
        menuflag = true;
        switch (opcion_seleccionada)
        {
        case 0:
            u8g2.clearBuffer();           // clear the internal memory
            u8g2.setFont(u8g_font_7x14B); // choose a suitable font
            // u8g2.drawStr(26, 10, "Buzzer"); // write something to the internal memory
            u8g2.drawXBMP(10, 10, 108, 44, GOT);
            u8g2.sendBuffer(); // transfer internal memory to the display
            gameofthronessong();
            botonState2 = 0;
            // u8g2.clearBuffer();
            // u8g2.setFont(u8g_font_7x14); // choose a suitable font
            // u8g2.drawXBMP(0, 22, 128, 23, epd_bitmap__selector);
            // u8g2.drawXBMP(120, 0, 8, 64, epd_bitmap__scrollbar);
            // u8g2.setFont(u8g_font_7x14);
            // u8g2.drawStr(26, 15, "Game of Thrones");
            // u8g2.setFont(u8g_font_7x14B);
            // u8g2.drawStr(26, 37, "Star Wars");
            // u8g2.setFont(u8g_font_7x14);
            // u8g2.drawStr(26, 59, "Rolita");
            // u8g2.sendBuffer(); // transfer internal memory to the display
            break;

        case 1:
            u8g2.clearBuffer(); // clear the internal memory
            // u8g2.drawXBMP(0, 0, 128, 64, marco);
            u8g2.setFont(u8g_font_7x14B);      // choose a suitable font
            u8g2.drawStr(26, 10, "Enconders"); // write something to the internal memory
            u8g2.setFont(u8g_font_7x14);
            u8g2.drawStr(5, 30, "Encoder Der: ");
            sprintf(Enco_Der, "%d", Robot.readRightEncoder());
            u8g2.drawStr(90, 30, Enco_Der);
            u8g2.drawStr(5, 42, "Encoder Izq: ");
            sprintf(Enco_Iz, "%d", Robot.readLeftEncoder());
            u8g2.drawStr(90, 42, Enco_Iz);
            u8g2.sendBuffer(); // transfer internal memory to the display

            actual_encoderiz = Robot.readLeftEncoder();
            actual_encoderder = Robot.readRightEncoder();
            if (actual_encoderiz != prev_encoderiz)
            {
                Robot.Sound(NOTE_E4);
                prev_encoderiz = actual_encoderiz;
            }
            else if (actual_encoderder != prev_encoderder)
            {
                Robot.Sound(NOTE_A4);
                prev_encoderder = actual_encoderder;
            }
            else
            {
                Robot.stopSound();
            }

            break;

        case 2:
            u8g2.clearBuffer();           // clear the internal memory
            u8g2.setFont(u8g_font_7x14B); // choose a suitable font
            u8g2.drawStr(40, 10, "IMU");  // write something to the internal memory
            u8g2.setFont(u8g_font_7x14);
            u8g2.drawStr(2, 25, "Angulo de rotacion");
            sprintf(Dato_IMU, "%d", Robot.IMUAngle());
            soundIMU = map(Robot.IMUAngle(), 0, 359, 31, 4978);
            Robot.Sound(soundIMU);
            u8g2.drawStr(50, 50, Dato_IMU);
            u8g2.sendBuffer(); // transfer internal memory to the display
            break;

        case 3:
            u8g2.clearBuffer();           // clear the internal memory
            u8g2.setFont(u8g_font_7x14B); // choose a suitable font
            u8g2.drawStr(26, 10, "LEDs"); // write something to the internal memory
            u8g2.sendBuffer();            // transfer internal memory to the display
            break;

        case 4:

            u8g2.clearBuffer();              // clear the internal memory
            u8g2.setFont(u8g_font_7x14B);    // choose a suitable font
            u8g2.drawStr(26, 10, "Motores"); // write something to the internal memory
            u8g2.drawXBMP(10, 25, 16, 16, epd_bitmap__motoricon);
            u8g2.drawXBMP(50, 25, 16, 16, epd_bitmap__motoricon);
            u8g2.sendBuffer(); // transfer internal memory to the display
            submenu = 4;
            break;

        case 5:

            u8g2.clearBuffer();                 // clear the internal memory
            u8g2.setFont(u8g_font_7x14B);       // choose a suitable font
            u8g2.drawStr(26, 10, "Sensores");   // write something to the internal memory
            u8g2.setFont(u8g_font_7x14);        // choose a suitable font
            u8g2.drawStr(10, 25, "Sensor FD:"); // write something to the internal memory
            u8g2.drawStr(10, 37, "Sensor FI:"); // write something to the internal memory
            u8g2.drawStr(10, 49, "Sensor LD:"); // write something to the internal memory
            u8g2.drawStr(10, 61, "Sensor LZ:"); // write something to the internal memory
            Robot.SensorsUpdate();
            sprintf(Sensor_FD, "%d", Robot.Val_Sensor(0));
            sprintf(Sensor_FI, "%d", Robot.Val_Sensor(1));
            sprintf(Sensor_LD, "%d", Robot.Val_Sensor(2));
            sprintf(Sensor_LI, "%d", Robot.Val_Sensor(3));
            u8g2.drawStr(85, 25, Sensor_FD);
            u8g2.drawStr(85, 37, Sensor_FI);
            u8g2.drawStr(85, 49, Sensor_LD);
            u8g2.drawStr(85, 61, Sensor_LI);
            u8g2.sendBuffer(); // transfer internal memory to the display
            break;
        case 6:
            u8g2.clearBuffer();
            // u8g2.drawXBMP(0, 0, 128, 64, marco);
            u8g2.setFont(u8g_font_7x14B);    // choose a suitable font
            u8g2.drawStr(35, 15, "Bateria"); // write something to the internal memory
            porcen_baterry = map(Robot.level_baterry(), 0, 7.5, 0, 100);
            sprintf(Bateria_lvl, "%d", porcen_baterry);
            u8g2.drawStr(9, 42, Bateria_lvl);
            lvl_baterry = map(Robot.level_baterry(), 0, 7.45, 0, 74);
            u8g2.drawXBMP(38, 22, 84, 33, bateria);
            u8g2.drawBox(42, 26, lvl_baterry, 25);
            u8g2.sendBuffer(); // transfer internal memory to the display
            break;

        default:
            break;
        }

        break;
    }
}
