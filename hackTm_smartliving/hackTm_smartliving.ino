#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
DHT dht(10, DHT11);
int temp;
int motorfata=4;
int motorspate=5;
int servopin=13;
int wet=1023;
int dry=0;
int pur=0;
int gazat=1023;
int stareaer;
int ledrosu=6;
int ledverde=7;
long durata;
int distanta;
int distantasiguranta;
int primit=48;
int trigpin=9;
int echopin=8;
int pozusa;

Servo Servo1;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(trigpin, OUTPUT); 
  pinMode(echopin, INPUT);
  pinMode(ledrosu, OUTPUT);
  pinMode(ledverde, OUTPUT);
  lcd.init();
  Serial.begin(9600);
  lcd.backlight();
  lcd.setBacklight(HIGH);
  dht.begin();
  pinMode(motorfata, OUTPUT);
  pinMode(motorspate, OUTPUT);
  Servo1.attach(servopin);
  Servo1.write(0); 

  lcd.setCursor(0,0);
  lcd.print("Bine ai");

  lcd.setCursor(0,1);
  lcd.print("venit acasa!");

  //delay(3000);

  lcd.clear();
  
}

void loop() {

  if (Serial.available())
  {
    primit=Serial.read();
    Serial.println(primit);
  }

  digitalWrite(ledrosu, HIGH);
  
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
  
  //dreapta
  while (primit==50)
    {
      if(pozusa<=180){
        pozusa++;
        Servo1.write(pozusa);
        digitalWrite(ledverde, HIGH);
        digitalWrite(ledverde, LOW);
      }
    }

  //stanga
  while (primit==51)
    {
      if(pozusa>=1){
        pozusa--;
        Servo1.write(pozusa);
        digitalWrite(ledverde, HIGH);
        digitalWrite(ledverde, LOW);
      }
    }

  /*digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  durata = pulseIn(echoPin, HIGH);

  distanta= durata*0.034/2;

  distantasiguranta = distanta;

  if(distantasiguranta<=100)
    {
      lcd.clear();
      lcd.setCursor(0,0)
      lcd.print("AVETI UN");
      lcd.setCursor(0,1);
      lcd.print("OASPETE!");

      if (primit==53)
        deschideusa();
    
    }*/
    
}
