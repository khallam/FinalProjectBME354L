//PID Code for Heater
#define RelayPin 2

//Define Parameters of interest
double Setpoint, Input, Output;

//Define aggressive and conservative PID parameters
double aggKp=2, aggKi=0.1, aggKd=5;
double consKp=1, consKi=0.05, consKd=2.5;

int Control(double user, double curtemp, int lastM)
{
  //Link the PID function
  PID myPID(&Input, &Output, &Setpoint, aggKp, aggKi, aggKd, DIRECT);
  pinMode(RelayPin, OUTPUT);

  int WindowSize=500;
  int windowStartTime;

  windowStartTime=lastM;
  Setpoint=user;
  Input=curtemp;
  myPID.SetOutputLimits(0,WindowSize);

  //Turn PID on
  myPID.SetMode(AUTOMATIC);

  double gap = Setpoint-Input; //distance away from setpoint
  if (gap>5)
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
  
  if (Output > ((now - windowStartTime) % WindowSize))
  {
    digitalWrite(RelayPin,HIGH);
  }
  
  if (Output < ((now - windowStartTime) % WindowSize))
  {
    digitalWrite(RelayPin,LOW);
  }
}








