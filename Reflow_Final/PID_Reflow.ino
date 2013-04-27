//PID Code for Heater
#define RelayPin 2

//Define Parameters of interest
double Setpoint, Input, Output;

//Define aggressive and conservative PID parameters
double aggKp=80, aggKi=4, aggKd=200;
double consKp=20, consKi=2, consKd=100;

int Control(double user, double curtemp)
{
  //Link the PID function
  PID myPID(&Input, &Output, &Setpoint, aggKp, aggKi, aggKd, DIRECT);


  int WindowSize=1000;
  unsigned long windowStartTime;

  windowStartTime=millis();
  Setpoint=user;
Input=curtemp;
  myPID.SetOutputLimits(0,WindowSize);

  //Turn PID on
  myPID.SetMode(AUTOMATIC);

  double gap = abs(Setpoint-Input); //distance away from setpoint
  if (gap<5)
  {  //we're close to setpoint, use conservative tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
    //we're far from setpoint, use aggressive tuning parameters
    myPID.SetTunings(aggKp, aggKi, aggKd);
  }

  myPID.Compute();

//  unsigned long now=millis();
//  if (now-windowStartTime > WindowSize)
//  {
//    windowStartTime +=WindowSize;
//  }
//  if (Output> now-windowStartTime) 
//  {
//    digitalWrite(RelayPin,HIGH);
//  }
//  else
//  {

    analogWrite(RelayPin,Output);
  }







