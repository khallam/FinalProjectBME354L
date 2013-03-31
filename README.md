FinalProjectBME354L
===================

\\ Tutorials 4-7 for Arduino



/*
Tutorial 7
*/

int sensePin = 0;
int ledPin = 9;

void setup()
{
  analogReference(DEFAULT); //isn't necessary
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  int val = analogRead(sensePin);
  val = constrain(val, 750, 900);
  int ledLevel = map(val, 750, 900, 255, 0);
  analogWrite(ledPin, ledLevel);
  
}


//Tutorial 7 (continued)
//Program by Jeremy Blum
//Turn on an LED if a room is dim, and motion is detected

//Define Pins
int motionPin = 0;
int lightPin = 1;
int ledPin = 9;

//Distance Variables 
int lastDist = 0;
int currentDist = 0;

//Threshold for Movement
int thresh = 200;

void setup()
{
  // The LED pin needs to be set as an output
  pinMode(ledPin, OUTPUT);
}
void loop()
{
  //read the sensor
  int lightVal = analogRead(lightPin);
  currentDist = analogRead(motionPin);
  
  //Does the current distance deviate from the last distance by more than the threshold?
  if ((currentDist > lastDist + thresh || currentDist < lastDist - thresh) && lightVal < 800)
  {
    digitalWrite(ledPin, HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
  lastDist = currentDist;
}

