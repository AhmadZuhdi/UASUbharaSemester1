
// 0x27

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27 // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

int n = 1;

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);


void setup() {
  // put your setup code here, to run once:
  lcd.begin (16,2); // set ukuran lcd (16x2)

  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home (); // go home

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //n++;
  int v = analogRead(0);
  float miniVolt = (v / 1024.0) * 5000;
  float celcius = miniVolt / 10;

  lcd.clear();
  lcd.print("Suhu: ");
  lcd.print(celcius);
  lcd.print("C"); 
  
  lcd.setCursor(0, 1); // set lcd ke line 2
  lcd.print("Klbp: ");
  lcd.print("Test");
  
  delay(250);
}
