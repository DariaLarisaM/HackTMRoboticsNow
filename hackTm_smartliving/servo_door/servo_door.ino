#include <Servo.h> 
#include <IRremote.h>

Servo motor_door;
#define IR_RECEIVE_PIN 12

int received = 48;
int pos;
int ledrosu=3;
int ledverde=2;

void setup() {
  Serial.begin(9600);
  motor_door.attach(13);
  motor_door.write(0);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(ledverde, OUTPUT);
  pinMode(ledrosu, OUTPUT);
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
      for(int i=0;i<=180;i++){
        pos++;
        motor_door.write(pos); 
        digitalWrite(ledverde, HIGH);
        delay(10);
        digitalWrite(ledverde, LOW);
      }
   }

  //stanga
  if(received == 8)
    {
      for(int i=180;i>=1;i--){
        pos--;
        motor_door.write(pos);
        digitalWrite(ledrosu, HIGH);
        delay(10);
        digitalWrite(ledrosu, LOW);
      }
    }
    delay(15);

}
