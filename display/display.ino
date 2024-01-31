
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin

int O_aman = 7;
int O_waspada = 8;
int O_bahaya = 9;
int buzzer = 12;

void setup(){
   lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  HC12.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(O_aman, OUTPUT);
  pinMode(O_waspada, OUTPUT);
  pinMode(O_bahaya, OUTPUT);
 
  lcd.setCursor(0,0);
  lcd.print("SYSTEM");
  lcd.setCursor(0,1);
  lcd.print("PROCESSING");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LANDSLIDE DETECTION");
  lcd.setCursor(0,1);
  lcd.print("BEGIN");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SCANNING");
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("SCANNING.");
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("SCANNING..");
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("SCANNING...");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SCANNING.");
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("SCANNING..");
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("SCANNING...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);  
}

void loop() {
  if(HC12.available() >1){
    int input = HC12.parseInt();
    float soil = HC12.read();
   
    //aman
    if(input == 1100)
    {
      Serial.println("2");
      lcd.clear();
      lcd.print("STATUS : SAFE");
      delay(1000);
    }
    else 
    {
      Serial.println("1");
    }
    //waspada
    if(input == 1110)
    {
      Serial.println("3");
      lcd.clear();
      lcd.print("STATUS : ALERT");
      digitalWrite(buzzer, HIGH);
      delay(1000);
      lcd.clear();
      lcd.print("STATUS : ALERT");
      digitalWrite(buzzer, LOW);
      delay(1000);
    }
    else 
    {
      Serial.println("1");
    }
    //bahaya
    if(input == 1101)
    { 
      Serial.println("6");
      lcd.clear();
      lcd.print("STATUS : DANGER!");
      digitalWrite(buzzer, HIGH);
      delay(500);
      lcd.clear();
      //lcd.print("STATUS : DANGER!");
      digitalWrite(buzzer, LOW);
      delay(1000);
    }
    else 
    {
      Serial.println("5");
    }
  }
  HC12.flush();
delay(20);
}

