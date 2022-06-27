#include <LiquidCrystal.h>
#define lm35 A7
#include<Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4);

char keys[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte sutunPin[4] = {27, 28, 29, 30};
byte kolonPin[3] = {26, 25, 24};

String password = "1234";
int position = 0;

int wrong = 0;

int redPin = 23;
int greenPin = 22;
Keypad keypad = Keypad(makeKeymap(keys), sutunPin, kolonPin, 4, 3);
int toplam = 0;
const int rs = 11, en = 10, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal ekran(rs, en, d4, d5, d6, d7);
int sensor = 13;
boolean sensordeger = 0;
boolean yangindeger = 0;
int tetik = 12;
int yanginsensor = 53;
int buzzer = 3;
float sicaklik;
int temp = 0;

void setup() {

  Serial.begin(9600);
  analogReference("INTERNAL");
  pinMode(sensor, INPUT);
  pinMode(tetik, OUTPUT);
  pinMode(yanginsensor, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  ekran.begin(16, 2);
  temp = analogRead(lm35);
  float temp2 = (temp / 1024.0) * 5000;
  sicaklik = temp2 / 10;

  termometre();
  


  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);


  lcd.init();
  lcd.init();
  lcd.backlight();
  
  lcd.clear();
  lcd.print(" Sifreyi Giriniz: ");
  delay(100);

  


}

void loop() {
 
  sensordeger = digitalRead(sensor);
  if (sensordeger == 1)
  {
    digitalWrite(tetik, HIGH);

  }
  else
  {
    digitalWrite(tetik, LOW);
  }
  yangindeger = digitalRead(yanginsensor);
  if (yangindeger == 1)
  {
    digitalWrite(buzzer, HIGH);

  }
  else
  {
    digitalWrite(buzzer, LOW);
  }

char pressed = keypad.getKey();
  String key[3];

  if (pressed)
  {
    lcd.clear();
    lcd.print(" Sifreyi Giriniz: ");
    lcd.setCursor(position, 2);
    lcd.print(pressed);
    delay(500);
    if (pressed == '*' || pressed == '#')
    {
      position = 0;
      kilit(true);
      lcd.clear();
    }

    else if (pressed == password[position])
    {
      key[position] = pressed;
      position++;
    }

    else if (pressed != password[position] )
    {
      wrong++;
      position ++;
    }

    if (position == 4) {
      if ( wrong > 0)
      {
        
        wrong = 0;
        position = 0;
        lcd.clear();
        lcd.setCursor(0, 2);
        lcd.print("    Yanlis Sifre!     ");
        delay(1000);
        kilit(true);
      }

      else if (position == 4 && wrong == 0)
      {
        position = 0;
        wrong = 0;
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("      HOSGELDINIZ!     ");
        lcd.setCursor(5, 2);
        lcd.print(" Kapi Acildi");
        delay(1000);
        kilit(false);
      }



    }

  }



}
void termometre()
{
  
  
    ekran.print("SICAKLIK:");
    ekran.print(sicaklik);
    ekran.println(" C");
    delay(3000);
    if(sicaklik<20)
    {
      ekran.clear();
      ekran.print("SICAKLIK DUSTU!");
     
    }
    if(sicaklik>30)
    {
      ekran.clear();
      ekran.print("SICAKLIK ARTTI");
      
    }

  

}



void kilit(int sifre)
{
  if (sifre)
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    delay(1000);
  }
  else
  {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);

  }
}
