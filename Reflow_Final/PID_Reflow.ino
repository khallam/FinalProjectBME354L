 //PID Code for Heater
#define RelayPin 2

//Define Parameters of interest
double Setpoint, Input, Output;

//Define aggressive and conservative PID parameters
double aggKp=5, aggKi=1, aggKd=10; 
double consKp=5, consKi=1, consKd=10;

int Control(double user, double curtemp, int lastM) //Make function to read thermocouple/control heater based on PID
{
  //Link the PID function
  PID myPID(&Input, &Output, &Setpoint, aggKp, aggKi, aggKd, DIRECT);
  
  pinMode(RelayPin, OUTPUT); //Heater Pin

  int WindowSize=500; //Define period of duty cycle
  int windowStartTime; //Define start time for all duty cycles

  windowStartTime=lastM; //lastM found in STAGES.INO zeros the millis value
  Setpoint=user-10; 
  Input=curtemp; //Current Temperature
  myPID.SetOutputLimits(0,WindowSize);  //Instead of 0-255

  //Turn PID on
  myPID.SetMode(AUTOMATIC);

  double gap = Setpoint-Input; //distance away from setpoint
  if (gap<10)
  {  //we're close to setpoint, use conservative tuning parameters
    myPID.SetTunings(consKp, consKi, consKd); 
  }
  else
  {
    //we're far from setpoint, use aggressive tuning parameters
    myPID.SetTunings(aggKp, aggKi, aggKd);
  }

  myPID.Compute(); //Compute pwm output

  unsigned long now=millis(); 
  int out=Output;
  lcd.setCursor(5,1);
  lcd.print(out);
  //Use modulus to find remainder of current time divided by window size
  
  if (Output > ((now - windowStartTime) % WindowSize)) //Define the ON states of the duty cycle based on PID output
  {
    digitalWrite(RelayPin,HIGH);
  }
  
  if (Output < ((now - windowStartTime) % WindowSize)) //Define the OFF states of the duty cycle based on PID output
  {
    digitalWrite(RelayPin,LOW);
  }
}
