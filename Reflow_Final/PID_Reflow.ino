//PID Code for Heater
#define RelayPin 1

//Define Parameters of interest
double Setpoint, Input, Output;

//Define aggressive and conservative PID parameters
double aggKp=2, aggKi=0.1, aggKd=5;
double consKp=0.5, consKi=0.025, consKd=1;


//Link the PID function
PID myPID(&Input, &Output, &Setpoint, aggKp, aggKi, aggKd, DIRECT);

int WindowSize=5000;
unsigned long windowStartTime;

/*
windowStartTime=millis();

Input=analogRead(A1)/0.005;
Setpoint= 150; //This is the user defined set temperature

myPID.SetOutputLimits(0,WindowSize);

//Turn PID on
myPID.SetMode(AUTOMATIC);

Input=analogRead(A1);

double gap = abs(Setpoint-Input); //distance away from setpoint
if (gap<10)
{  //we're close to setpoint, use conservative tuning parameters
  myPID.SetTunings(consKp, consKi, consKd);
}
else
{
  //we're far from setpoint, use aggressive tuning parameters
  myPID.SetTunings(aggKp, aggKi, aggKd);
}

myPID.Compute();

unsigned long now=millis();
if (now-windowStartTime>WindowSize)
{
  windowStartTime +=WindowSize;
}
if (Output> now-windowStartTime) 
{
  digitalWrite(RelayPin,HIGH);
}
else
{
  analogWrite(RelayPin,Output);
}
lcd.setCursor(1,1);
lcd.print(Output);

return RelayPin

*/

