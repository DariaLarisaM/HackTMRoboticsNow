#include <DHT.h>
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
DHT dht(10, DHT11);
int temp;
int wet=1023;
int dry=0;
int pur=0;
int gazat=1023;
int stareaer;
long durata;
int distanta;
int distantasiguranta;
int primit=48;
int trigpin=9;
int echopin=8;
int pozusa;
int microfon=7;
int ploaie=6;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(trigpin, OUTPUT); 
  pinMode(echopin, INPUT);
  pinMode(microfon, INPUT);
  pinMode(ploaie, INPUT);
  lcd.init();
  Serial.begin(9600);
  lcd.backlight();
  lcd.setBacklight(HIGH);
  dht.begin();
  
  lcd.setCursor(0,0);
  lcd.print("Bine ai");

  lcd.setCursor(0,1);
  lcd.print("venit acasa!");

  delay(3000);

  lcd.clear();
  
}

void loop() {
  
  temp = dht.readTemperature();

  int sensorumiditate = analogRead(A0);

  int senzorgaz=analogRead(A3);

  stareaer=map(senzorgaz, pur, gazat, 0, 100);

  delay(100);

  lcd.setCursor(0,0);
  lcd.print("Pur. Aer: ");
  lcd.print(stareaer);
  lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");

  if(stareaer>=55)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("E NEVOIE DE");
      lcd.setCursor(0,1);
      lcd.print("AERISIRE!");
      delay(3000);   
      lcd.clear();
    }

  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  durata = pulseIn(echopin, HIGH);

  distanta= durata*0.034/2;

  distantasiguranta = distanta;

  if(distantasiguranta<=100)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Aveti un");
      lcd.setCursor(0,1);
      lcd.print("Oaspete!");
      delay(100);
    }

   if(digitalRead(microfon)==HIGH)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ZGOMOT");
      lcd.setCursor(0,1);
      lcd.print("Inchidere geam!");
      delay(3000);   
      lcd.clear();
    }

    if(digitalRead(ploaie)==LOW)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PLOUA!");
      lcd.setCursor(0,1);
      lcd.print("Inchidere geam!");   
      delay(3000);
      lcd.clear();
    }
}
