#include <Arduino.h>
#include <ArtilSolver.h>
#include <U8g2lib.h>

#include <Wire.h>

//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 16, /* data=*/ 17, /* reset=*/ U8X8_PIN_NONE);

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

ArtilSolver Robot;

void setup(void) {
  Robot.init();
  u8g2.begin();
  Serial.begin(115200);
}

void loop(void) {

  Serial.print("IMU: ");
  Serial.println(Robot.IMUAngle());
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(0,10,"HHHHI");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display

  
}
