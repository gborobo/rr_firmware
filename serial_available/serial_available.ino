/////////////////////////////////////////////////////////////////
// This is where we left off trying to send live decimal input //
// and receive a decimal value. Out first code used parseInt() //
// which was slow, so we're trying to do it based on reading   //
// the input in bytes (max 3 digits; one digit at a time) and  //
// feeding this into a function that will convert it to decimal//
/////////////////////////////////////////////////////////////////


int qTest = 0;

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop()
{
   Serial.println(Serial.available());
   qTest = Serial.read();
   Serial.println(qTest);
   Serial.println("-------");
   delay(1000);
   
}
