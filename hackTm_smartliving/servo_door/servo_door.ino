#include <Servo.h> 
#include <IRremote.h>

Servo motor_door;
#define IR_RECEIVE_PIN 12

int received = 48;
int pos;
int ledrosu=3;
int ledverde=2;
int dist_semnal = 8;
void setup() {
  Serial.begin(9600);
  motor_door.attach(13);
  motor_door.write(0);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(ledverde, OUTPUT);
  pinMode(ledrosu, OUTPUT);
  pinMode(dist_semnal, INPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    Serial.println(IrReceiver.decodedIRData.command);
    received=IrReceiver.decodedIRData.command;
  }
  //dreapta
  if(received == 90 )
   {
      while(pos <= 180){
        motor_door.write(pos); pos++;  
        digitalWrite(ledverde, HIGH);
        delay(10);
        digitalWrite(ledverde, LOW);
      }
   }

  //stanga
  if(received == 8)
    {
        while(pos >= 1){
          motor_door.write(pos); pos--;
          digitalWrite(ledrosu, HIGH);
          delay(10);
          digitalWrite(ledrosu, LOW);
        }
        
    }
    if(digitalRead(dist_semnal) == HIGH){
      while(pos <= 180){
         motor_door.write(pos); pos++;
         digitalWrite(ledverde, HIGH);
         delay(10);
         digitalWrite(ledverde, LOW);
      }
      delay(100);
    }
    delay(15);

}
