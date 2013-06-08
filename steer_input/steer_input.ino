#include <Servo.h>

Servo brake;

int center = 100;

byte byteRead;

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

  if (Serial.available()) {
    /* read the most recent byte */
    byteRead = Serial.read();
    /*ECHO the value that was read, back to the serial port. */
    Serial.write(byteRead);
    
  }
  
  /*
  val = analogRead(pot);
  val = map(val, 0, 1023, 0, 179);
  brake.write(val);
  delay(15);
  */
}
  
