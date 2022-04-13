#include <LiquidCrystal.h>

LiquidCrystal lcd = LiquidCrystal(12, 11, 5, 4, 3, 2);
int x;
int t;
int odl;

void setup() {
  lcd.begin(16,2);
  pinMode(10, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);
}

void loop() {
  
  x = digitalRead(10);
  lcd.clear();
  lcd.setCursor(0, 1);
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);
  t = pulseIn(9, HIGH);
  odl = t / 2/29.1;
  if(odl > 200) {
    lcd.write("OoR");
  }
  else{
    lcd.print(odl);
  }
  //delay(30);
  lcd.setCursor(0,0);
  if(x){
    lcd.write("ruch");
  }
  else {
    lcd.write("brak ruchu");
  }
  delay(500);
}
