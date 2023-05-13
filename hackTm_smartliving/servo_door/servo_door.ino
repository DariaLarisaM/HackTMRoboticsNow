#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>

Servo motor_door;
int received = 48;
int pos = 0;
void setup() {
  Serial.begin(9600);
  motor_door.attach(13);
  motor_door.write(1);
}

void loop() {
  if(Serial.available()){
    received = Serial.read();
  }
  //dreapta
  if(received == 50){
      if(pos < 180){
        motor_door.write(pos); pos++;
      }
   }

  //stanga
  if(received == 51)
    {
      if(pos >= 1){
        motor_door.write(pos);
        pos--;
      }
    }
    delay(15);

}
