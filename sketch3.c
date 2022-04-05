#include <LiquidCrystal.h>
#include <TimerOne.h>
 
LiquidCrystal lcd = LiquidCrystal(12, 11, 7, 6, 5, 4);
float x = 0;
TimerOne timer1;
int c = HIGH;
bool previous;
int mode = 0;
 
void func(){
  lcd.clear();
  x = analogRead(5);
  x = (x/1023)*5;
  lcd.write("U = ");
  lcd.setCursor(4, 0);
  lcd.print(x);
  lcd.setCursor(9,0);
  lcd.write("V");
}
 
void setup() {
   lcd.begin(16,2);
  pinMode(2, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  timer1.initialize(500000);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  previous = c;
  c = digitalRead(8);
  delay(20);
  if(c == LOW && previous == HIGH){
    mode++;
    if (mode == 2){
      mode = 0;
    }
  }
  if(mode == 1){
    attachInterrupt(digitalPinToInterrupt(2), func, LOW);
    detachInterrupt(digitalPinToInterrupt(2));
  }
  else{
    timer1.attachInterrupt(func);
    timer1.detachInterrupt();
  }
}
