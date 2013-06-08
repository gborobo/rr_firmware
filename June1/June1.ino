#include <Servo.h>
Servo test1; 
int turn = 90; //initializing center position


void setup(){
  Serial.begin(9600);
  test1.attach(3);
}

void loop() {
  if (Serial.available() > 0)
  {
    //turn = Serial.parseInt();
  test1.write(Serial.parseInt());
  }
}
