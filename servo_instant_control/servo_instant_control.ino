// want to read in a decimal number of an arbitrary amount of digits, up to some Arduino-specified maximum
#include <Servo.h>


int maxDigits = 8; // max number of accepted digits

int incomingDigits = 0; // counter for digits
boolean numFill = false;

int serialOld = -1; // init
int serialNew = 0; // init
boolean waitData = true; // if waiting for data on stream; init
int serialBufferDelay = 5; // ms to wait inbetween bytes transferred (can be tuned)

// actuator stuff - assuming servo

Servo act1;
int act1Out = 3;

void setup() 
{
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  
  act1.attach(act1Out);
  act1.write(90);
}

void loop()
{
  // only accept numbers of given digit length
  
  while (Serial.available() > 0 && waitData) // trigger when the first byte of a stream comes into the buffer (arduino runs so fast it only sees the first byte
  {
    
    // update the last count of bytes available from arduino's point of view (it runs really fast)
    serialNew = Serial.available(); // check the buffer (will return 1 on first byte before the others have arrived
    Serial.print("serialNew = ");
    Serial.println(serialNew);
    
    if (serialNew == serialOld) // serial
    {
      waitData = false; // done waiting on the computer, no more bytes sent within timeout period
      Serial.println("Stream buffer timed out. No more bytes in queue.");
    }    
    
    else
    {
      serialOld = serialNew; // store value of the new Serial.available() in serialOld
    }
    
    delay(serialBufferDelay); // wait for new byte to come in at 9600 baud
 
  }
  
  if (serialNew > 0)
  {
    incomingDigits = serialNew;
    serialNew = 0; // reset
    waitData = true; // reset
    serialOld = -1; // reset; can be 0 as well (I think)
  }

  
  if ((incomingDigits > 0) && (incomingDigits <= maxDigits))
  {
    Serial.println("---Acceptable input received---");
    Serial.print("incomingDigits = ");
    Serial.println(incomingDigits);
 
    int digitwiseNum[incomingDigits];
    //numFill = true;  
  
    for (int i = 0; i < incomingDigits; i++) // could also do while (Serial.available() > 0), but I want that counter in
    {
      // fill the array
      digitwiseNum[i] = Serial.read() - 48;  // encoding?
      Serial.print("digitwiseNum[i] = ");
      Serial.println(digitwiseNum[i]);
    }

    // serial buffer should be empty    
    
    // must pass both the digitwiseNum array AND its member size to the parse function
    // passing an array to a function in C++ is by reference by default, and a POINTER is passed instead
    // using the sizeof function inside that function returns the size of the array pointer in bytes (2 bytes)
    // therefore, calling sizeof(incomingArray) in the parse function below ALWAYS returned 2 and caused serious problems.
    int output = parse(digitwiseNum, sizeof(digitwiseNum)/sizeof(int));

    // print the number
    Serial.println("---writing to actuator---");
    Serial.print("Actuator 1 output = ");
    Serial.println(output);
    Serial.println("------------------------");
    
    act1.write(output); // rounding error exists - see parse function below for details
  
  }
  
  incomingDigits = 0; // reset
}

int parse(int numArray[], int numDigits)
{
  // declare holder variable for total
  int outputNum = 0;
  // find size of incoming digitwise array and use that as control counter
  
  Serial.println("---parse function output---");
  
  Serial.print("numDigits = ");
  Serial.println(numDigits);
  
  // loop through all the digits
  for (int j = 0; j < numDigits; j++)
  {
    // ex. 123 is stored as array[0]=1, array[1]=2, array[2]=3
    // want to multiply MSB (1, array[0]) by 10^2
    // but 2 here is # of digits - 1
    // and the power of 10 decreases by 1 every digit
    // at j = 1 (second run), array[1] * 10^(3 - 1 - 1) = 2*10^1
    // eventually it should hit 0, which means multiplying by 1
    // debug
    Serial.print("numArray[j] = ");
    Serial.println(numArray[j]);
    outputNum += numArray[j] * pow(10, numDigits - 1 - j); // EXHIBITS ROUNDING ERROR, CAUTION!
  }
  return outputNum;
}

//void loop() {


        //if (Serial.available() >// 0) {

              //incomingByte = Serial.parseInt();
              //incomingByte = Serial.parseInt();

             //Serial.print("I received: ");
             // Serial.print(Serial.read() - 48);
             // Serial.print(incomingByte, DEC);
              //Serial.print("\n");
      //}
//} 
