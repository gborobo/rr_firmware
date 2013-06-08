#include <Servo.h>

Servo brake;

const int pot = 5;

void setup()
{
  pinMode(pot,INPUT);
  brake.attach(3);
}

void loop()
{
  int val;
  val = analogRead(pot);
  val = map(val, 0, 1023, 0, 179);
  brake.write(val);
  delay(15);
}
  
