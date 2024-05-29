//130 degress = off. Directly infront of lens
//170 degrees = lens exposed.

const int OpenAngle = 60;
const int ClosedAngle = 150;
// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 3; 
int buttonPin=4;
// Create a servo object 
Servo Servo1;

void setup() 
{ // We need to attach the servo to the used pin number 
  Servo1.attach(servoPin); 
  Serial.begin(9600);
  Serial.println("Servo Control");
  Servo1.write(OpenAngle);
  pinMode(buttonPin,INPUT_PULLUP);
}

int buttonopen=1;
void loop()
{ 
  if (Serial.available()>0)
  {  
    int open = Serial.parseInt();
    //Servo1.write(open);
    if (open) 
    {// Make servo go to angle typed
      Servo1.write(OpenAngle);
    } else
    {
      Servo1.write(ClosedAngle);
    }
    while (Serial.available()) Serial.read();
  }
  if (!digitalRead(buttonPin))
  {
    delay(10);
     buttonopen=1-buttonopen; 
    if (buttonopen) 
    {// Make servo go to angle typed
      Servo1.write(OpenAngle);
    } else
    {
      Servo1.write(ClosedAngle);
    }
    delay(1000);
  }
  
}
