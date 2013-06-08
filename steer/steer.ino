#include <Servo.h>

Servo brake;

int center = 90;

void setup()
{
  brake.attach(3);
  
  // start serial comms
  Serial.begin(9600);
  //print test messsage
  Serial.println("Hello world!");
  
  // set to 0, find zero position

  brake.write(center);
  
}

void loop()
{

  // back and forth continuous
  for (int i = 1; i <= 3; i++)
  {
    brake.write(center+10*i);
    delay(1000);
  
    brake.write(center);
    delay(1000);
  
    brake.write(center-10*i);
    delay(1000);
  
    brake.write(center);
    delay(1000);
  }
  
  /*
  val = analogRead(pot);
  val = map(val, 0, 1023, 0, 179);
  brake.write(val);
  delay(15);
  */
}
  
