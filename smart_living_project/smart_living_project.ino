#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <dht.h> // librarie pentru temperatura si umiditate
#include <IRremote.h>

#define open_window   0x18
#define close_window  0x52
#define open_door     0x5A
#define close_door    0x8
#define pin_raining   A2

#define IR_RECEIVE_PIN 7
//where the functions are declared
void raining();
void temperature();
void noise();


//variables
//int ir_controller_pin = 7;
int received = 48;
int position_window = 0;
int receiver = 7;
int trig = 3;
int aerisire = 9;
int zgomot = 10;
int temp = 11; 
bool window_is_opened = false;
bool door_is_opened = false;

//objects
Servo window_motor;
Servo door_motor;

void setup(){
  Serial.begin(9600);
  pinMode(receiver,INPUT);
  pinMode(trig, INPUT);
  pinMode(aerisire, INPUT);
  pinMode(zgomot, INPUT);
  pinMode(temp, INPUT);
  IrReceiver.begin(IR_RECEIVE_PIN);
  window_motor.attach(7);
  window_motor.write(20);
  
}

void loop(){
  if(Serial.available()){
    received = Serial.read();
  }
  if(received == 49)
    {
      if(position_window < 490){
        window_motor.write(position_window);
        position_window++;
        //delay(15);
      }
      window_is_opened = true;
    }
  
    if(received == 52)
    {
      if(position_window >= 20){
        window_motor.write(position_window), position_window--;
        //delay(15);
      }
      if(position_window == 0)
        window_is_opened = false;
    }
  if(digitalRead(trig) == HIGH){
    close_window_function();
    delay(500);
  }
  else if(digitalRead(aerisire) == HIGH){
    close_window_function();
    delay(500);
  }
  else if(digitalRead(temp) == HIGH){
    close_window_function();
    delay(500);
  } 
  else if(digitalRead(zgomot) == HIGH){
     close_window_function();
    delay(500);
  }
  delay(20);
  
  
}

void close_window_function(){
  while(position_window >= 20){
      window_motor.write(position_window);
      position_window--;
  }
  window_is_opened = false;
}


/*
  commands:
  48 - nimic
  49 - open the window
  52 - close the window
  daca ploua il inchid 
  daca sunt prea multi decibeli il inchid
  pinul 8 - window motor
  pinul 9 - door motor
  24 - sus remote
  82 - jos remote
  90 - dreapta remote
  8 - stanga remote
  28 - ok remote
  
  
  
 */
