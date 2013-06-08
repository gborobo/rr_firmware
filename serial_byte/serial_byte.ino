/////////////////////////////////////////////////////////////////
// This is where we left off trying to send live decimal input //
// and receive a decimal value. Out first code used parseInt() //
// which was slow, so we're trying to do it based on reading   //
// the input in bytes (max 3 digits; one digit at a time) and  //
// feeding this into a function that will convert it to decimal//
/////////////////////////////////////////////////////////////////

int incomingByte = 0;   // for incoming serial data
int a[3] = {0};
int m = 0;
boolean numFill = false;

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop()
{
   while(Serial.available() > 0)
   {
      a[m] = Serial.read() - 48;
      
      delay(10);
      m++;
      
      numFill = true;
   }
   
   if (numFill)
   {
     Serial.print("Received = ");
     Serial.println(parse(m));
     
     // reset numFill flag
     numFill = false;
     m = 0;
   }
   
   
}

int parse(int n){
    if (n == 1)
      return a[n-1];

    else if (n == 2)
      return a[n-2]*10 + a[n-1];

    else if (n == 3)
      return a[n-3]*100 + a[n-2]*10 + a[n-1];
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
