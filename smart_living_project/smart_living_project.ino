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
int position_door = 0;
bool window_is_opened = false;
bool door_is_opened = false;

//objects
Servo window_motor;
Servo door_motor;
IRrecv ir_controller(7);

void setup(){
  Serial.begin(9600);
  pinMode(receiver,INPUT);
  IrReceiver.begin(IR_RECEIVE_PIN);
  window_motor.attach(A3);
  door_motor.attach(9);
  window_motor.write(20);
  
}

void loop(){
 
  /*if(ir_controller.decode(&ir_results)){
    //Serial.println(ir_results.value, HEX);
    Serial.println(ir_controller.decodedIRData.command);
           if (ir_controller.decodedIRData.command == 0x18)  { /// open window
               if(position_window < 90){
                 window_motor.write(position_window), position_window++;
                 delay(15);
                }
                window_is_opened = true;
            } else if (ir_controller.decodedIRData.command == 0x52) { // close window
                if(position_window >= 1){
                  window_motor.write(position_window), position_window--;
                  delay(15);
                }
                if(position_window == 0)
                  window_is_opened = false;
            } else if (ir_controller.decodedIRData.command == 0x11) {
               
            } else if (ir_controller.decodedIRData.command == 0x11) {
                
            }
        

        ir_controller.resume();*/

   if (IrReceiver.decode()) {
    IrReceiver.resume();
    Serial.println(IrReceiver.decodedIRData.command);}
  
  if(Serial.available()){
    received = Serial.read();
  }
  /*if(received == 49){ // open the window
    if(position_window < 90){
      window_motor.write(position_window), position_window++;
      //delay(15);
    }
    window_is_opened = true;
  }
  if(received == 52){ // close the window
    if(position_window >= 1){
      window_motor.write(position_window), position_window--;
      //delay(15);
    }
    if(position_window == 0)
      window_is_opened = false;
  }*/

  
  delay(15);
  ploua();
  delay(15);

  if(received==24)
  {
    if(position_window < 490){
      window_motor.write(position_window);
      position_window++;
      //delay(15);
    }
    window_is_opened = true;
  }

  if(received==82)
  {
    if(position_window >= 20){
      window_motor.write(position_window), position_window--;
      //delay(15);
    }
    if(position_window == 0)
      window_is_opened = false;
  }
}
void close_window_function(){
  while(position_window){
      window_motor.write(position_window);
      position_window--;
  }
  window_is_opened = false;
}
void ploua(){
  int raining_value = analogRead(pin_raining);
  if(window_is_opened && raining_value < 400){
    close_window_function();
  }
  
}
void noise(){

  
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
