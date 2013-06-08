#include <Servo.h>

Servo brake;

const int pot = 5;
int val;

void setup()
{
  pinMode(pot,INPUT);
  brake.attach(3);
}

void loop()
{
  val = analogRead(pot);
  val = map(val, 0, 1023, 0, 179);
  brake.write(val);
  delay(15);
}
  
