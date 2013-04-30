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


  int WindowSize=1000;
  int windowStartTime;

  windowStartTime=lastM;
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

  int now=millis();
  lcd.setCursor(2,1);
  lcd.print(((now - windowStartTime) % WindowSize));
  
  
  if (Output > ((now - windowStartTime) % WindowSize))
  {
    digitalWrite(RelayPin,HIGH);
  }
  
  if (Output < ((now - windowStartTime) % WindowSize))
  {
    digitalWrite(RelayPin,LOW);
  }
  
 
 /* 
  if (now-windowStartTime > WindowSize)
  {
    windowStartTime =lastM + WindowSize;
  }
  if (Output> now-windowStartTime) 
  {
    digitalWrite(RelayPin,HIGH);
  }
  if (Output < now-windowStartTime)
  {
   digitalWrite(RelayPin,LOW);
  }
  */
}








