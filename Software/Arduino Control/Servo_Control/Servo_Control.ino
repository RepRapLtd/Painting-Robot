//130 degress = off. Directly infront of lens
//170 degrees = lens exposed.

const int OpenAngle = 170;
const int ClosedAngle = 130;
// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 3; 
// Create a servo object 
Servo Servo1; 
void setup() 

{ // We need to attach the servo to the used pin number 
Servo1.attach(servoPin); 
Serial.begin(9600);
Serial.println("Servo Control");
Servo1.write(OpenAngle);}


void loop(){ if (Serial.available()>0)
{int open =Serial.parseInt();
    if (open) 
   {// Make servo go to angle typed
   Servo1.write(OpenAngle); } else
  {Servo1.write(ClosedAngle);}
   while (Serial.available())
   Serial.read();}
}
