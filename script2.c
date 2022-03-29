#include"i2c_BMP280.h"
#include "i2c.h"
#include "i2c_Sensor.h"
#include <LiquidCrystal.h>
 
LiquidCrystal lcd = LiquidCrystal(12, 11, 5, 4, 3, 2); 
BMP280 bmp280;
float p = 0;
float t = 0;
 
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  bmp280.initialize();
}
 
void loop() {
  // put your main code here, to run repeatedly:
  bmp280.awaitMeasurement();
  bmp280.getPressure(p);
  bmp280.getTemperature(t);
  lcd.clear();
  lcd.print(t);
  lcd.setCursor(6,0);
  lcd.write("C");
  lcd.setCursor(0,1);
  lcd.print(p);
  lcd.setCursor(10, 1);
  lcd.write("Pa");
  delay(1000);
}
