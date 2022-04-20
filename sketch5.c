#include <SPI.h>
#include <stdlib.h>
#include <math.h>
#include "LCD.h"
#include "DEV_Config.h"
#include "ADXL345.h"

ADXL345 acc;
float x, y, z, pitch, roll, yaw;
char ax[10];
char ay[10];
char az[10];
char pi[10];
char ro[10];
char ya[10];

void setup() {
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_DC, OUTPUT);
  
  acc.begin();
  acc.setRange(ADXL345_RANGE_4G);

  SPI.begin();
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));

  LCD_SCAN_DIR Lcd_ScanDir = SCAN_DIR_DFT;
  LCD.LCD_Init(Lcd_ScanDir);
  LCD.LCD_Clear(BLACK);
}

void loop() {
  Vector norm = acc.readNormalize();
  Vector filt = acc.lowPassFilter(norm, 0.15);
  x = filt.XAxis;
  y = filt.YAxis;
  z = filt.ZAxis;
  pitch = atan(x/sqrt(y*y+z*z))*(180/PI);
  roll = atan(y/sqrt(x*x + z*z))*(180/PI);
  yaw = atan(z/sqrt(x*x + z*z))*(180/PI);
  
  LCD.LCD_Clear(BLACK);
  dtostrf(x, 2, 2, ax);
  dtostrf(y, 2, 2, ay);
  dtostrf(z, 2, 2, az);
  dtostrf(pitch, 2, 2, pi);
  dtostrf(roll, 2, 2, ro);
  dtostrf(yaw, 2, 2, ya);
  
  LCD.LCD_DisplayString(0, 6, "ax = ", &Font12, BLACK, YELLOW);
  LCD.LCD_DisplayString(40, 6, ax, &Font12, BLACK, YELLOW);
  
  LCD.LCD_DisplayString(0, 26, "ay = ", &Font12, BLACK, YELLOW);
  LCD.LCD_DisplayString(40, 26, ay, &Font12, BLACK, YELLOW);
  
  LCD.LCD_DisplayString(0, 46, "az = ", &Font12, BLACK, YELLOW);
  LCD.LCD_DisplayString(40, 46, az, &Font12, BLACK, YELLOW);

  LCD.LCD_DisplayString(0, 66, "pitch = ", &Font12, BLACK, YELLOW);
  LCD.LCD_DisplayString(60, 66, pi, &Font12, BLACK, YELLOW);

  LCD.LCD_DisplayString(0, 86, "roll = ", &Font12, BLACK, YELLOW);
  LCD.LCD_DisplayString(60, 86, ro, &Font12, BLACK, YELLOW);

  LCD.LCD_DisplayString(0, 106, "yaw = ", &Font12, BLACK, YELLOW);
  LCD.LCD_DisplayString(60, 106, ya, &Font12, BLACK, YELLOW);
  
  //
  delay(200);
}
