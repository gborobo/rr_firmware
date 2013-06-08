#include <Servo.h>

Servo brake;
#define POT 5

int val;

void setup()
{
  pinMode(POT,INPUT);
  brake.attach(3);
}

void loop()
{
  val = analogRead(POT);
  val = map(val, 0, 1023, 0, 179);
  brake.write(val);
  delay(15);
}
  
