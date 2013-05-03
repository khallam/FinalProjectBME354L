//PID control code for Stages.INO

//Pin for Heater
#define RelayPin 2

//Define Parameters of interest
double Setpoint, Input, Output;

//Define aggressive and conservative PID parameters (Chosen based on experimentation and effect of each parameter
double aggKp=2, aggKi=.1, aggKd=5; 
double consKp=10, consKi=.02, consKd=10;

int Control(double user, double curtemp, int lastM) //Make function to read thermocouple/control heater based on PID
{
  //Link the PID function
  PID myPID(&Input, &Output, &Setpoint, aggKp, aggKi, aggKd, DIRECT);

  pinMode(RelayPin, OUTPUT); //Heater Pin

  int WindowSize=500; //Define period of duty cycle
  int windowStartTime; //Define start time for all duty cycles

  windowStartTime=lastM; //lastM found in STAGES.INO --> zeros the millis value
  if (user>200){
    Setpoint=user-3;      //Decrease the setpoint given to PID by 3 C for the reflow temp to account for the closed heater enviroment
  }
  if (user<200){          //Decrease the setpoint given to PID by 10 C for the soak temp to account for the closed heater enviroment
    Setpoint=user-10;
  }
  Input=curtemp; //Current Temperature
  myPID.SetOutputLimits(0,WindowSize);  //Instead of 0-255

  //Turn PID on
  myPID.SetMode(AUTOMATIC);

  double gap = Setpoint-Input; //distance away from setpoint
  if (gap<10)
  {  //we're close to setpoint, use conservative tuning parameters (more sensitive to error)
    myPID.SetTunings(consKp, consKi, consKd); 
  }
  else
  {
    //we're far from setpoint, use aggressive tuning parameters (less sensitive)
    myPID.SetTunings(aggKp, aggKi, aggKd);
  }

  myPID.Compute(); //Compute pwm output

  unsigned long now=millis();  //Count current millis time

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

