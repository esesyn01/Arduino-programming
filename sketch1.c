#include <LiquidCrystal.h>
//#include <Serial.h>

byte emoji[8] = 
{ B00000,
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100,
  B00000
};
byte znak = 0;
LiquidCrystal LCD = LiquidCrystal(12, 11, 5, 4, 3, 2);
int col = 14;
int row = 0;
void setup() {
  LCD.createChar(0, emoji);
  LCD.begin(16, 2);
  LCD.clear();
  LCD.setCursor(col, row);
  LCD.write(byte(0));
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()){
    znak = Serial.read();
    if(znak == 'a'){
      col -= 1;
      if(col == -1) {
        col = 15;
      }
    }
    if(znak == 'w'){
      row -= 1;
      if(row == -1){
        row = 1;
      }
    }
    if(znak == 's'){
      row += 1;
      if(row == 2){
        row = 0;
      }
    }
    if(znak == 'd'){
      col += 1;
      if(col == 16) {
        col = 0;
      }
    }
    LCD.clear();
    LCD.setCursor(col, row);
    LCD.write(byte(0));
  }
}