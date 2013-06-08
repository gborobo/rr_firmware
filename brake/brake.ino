#include <Servo.h>

Servo brake;
#define POT 5

void setup()
{
  pinMode(POT,INPUT);
  brake.attach(3);
}

void loop()
{
  int val;
  val = analogRead(POT);
  val = map(val, 0, 1023, 0, 179);
  brake.write(val);
  delay(15);
}
  
