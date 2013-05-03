//Control of stages of reflow curve for Reflow_Final.INO

//Define variables
int refstage = 0; //Constant to control progress of stages
int curtime; //from STOPWATCH.INO
String dispstage;          
unsigned long lastM;
int maxPeak1=0;
int maxPeak2=0;
int presoakerr;
int reflowerr;

char Reflow_Stage(int curtemp, int soaktemp, int reflowtemp, int soaktime, int reflowtime) //Function to run through all stages--Used in REFLOW_FINAL.INO
{
  if (refstage == 0){ //This stage simply records time to reach this point, and freezes lastM
    lastM = millis();
    refstage = 1; //move on to Pre-Soak
  }

  if (refstage == 1){                              //Pre-Soak stage--dependent upon temperature condition
    dispstage = "Presoak";
    Control(soaktemp,curtemp,lastM);               //PID function modulates temp to soaktemp 
    lcd.setCursor(3,0);                            //Print current stage
    lcd.print(dispstage);

    if (curtemp >= soaktemp){                      //Condition to move on to soak stage
      lcd.clear();                                 //Clear the screen before moving on
      refstage = 2;
      lastM=millis();                              //Freeze millis time as lastM before moving on
    }
  }

  if (refstage == 2){                              //Soak stage--dependent upon time condition
    dispstage = "Soak";
    curtime = Stopwatch(soaktime, lastM);          //Record current time based on lastM
    printtime = soaktime-curtime;                  //Time left in the stage
    lcd.setCursor(3,0);
    lcd.print(dispstage);                          //Print current stage
    Control(soaktemp,curtemp,lastM);               //PID functions keeps temp at soaktemp

    if (maxPeak1 <= curTemp){                       //Record max temp of this SOAK
      maxPeak1 = curTemp;
    }
    else if (maxPeak1>curTemp){         
      maxPeak1 = maxPeak1;
    }

    if (curtime >= soaktime){                      //Time condition to move on to pre-reflow
      refstage = 3; 
      lcd.clear();                                 //Clear the screen before moving on
    }
  }

  if (refstage == 3){                              //Pre-Reflow Stage--Dependent upon temperature condition 
    dispstage = "PreRef";
    lcd.setCursor(3,0);
    lcd.print(dispstage);                          //Print current stage

      Control(reflowtemp,curtemp,lastM);             //This PID ramps up until the temperature reaches reflow temp

    if (curtemp >= 217){                           //Condition to move on to reflow temp --NOT user input (Reflow starts at 217 C)
      lcd.clear();                                 //Clear the screen before moving on
      refstage = 4;
      lastM=millis();                              //Freeze millis as lastM before moving on
    }
  }

  if (refstage == 4){                              //Reflow Stage--Time dependent
    dispstage = "Reflow";
    curtime = Stopwatch(reflowtime,lastM);         //Current time based on zeroed time
    printtime=reflowtime-curtime;                  //Display time left

    lcd.setCursor(3,0);
    lcd.print(dispstage);                          //Display current stage

      if (maxPeak2 <= curTemp){                       //Find max temp of REFLOW
      maxPeak2 = curTemp;
    }
    else if (maxPeak2>curTemp){               
      maxPeak2 = maxPeak2;
    }

    Control(reflowtemp,curtemp,lastM);             //PID function to keep temp at reflow temp

    if (curtime >= reflowtime){                    //Condition to move on to cooling stage
      lcd.clear();                                 //Clear the screen before moving on
      refstage = 5;
    }
  }

  if (refstage == 5){                              //Cooling stage--Dependent on temperature
    dispstage = "Cooling (FAN ON)";
    lcd.setCursor(0,0);
    lcd.print(dispstage);                          //Display stage

      Control(25,curtemp,lastM);                     //PID controls temperature at room temperature

    lcd.setCursor(1,1);                            //Print the max soak and reflow temp while cooling the oven
    lcd.print(maxPeak1);
    lcd.setCursor(5,1);
    lcd.print(maxPeak2);
    delay(200);                                    //Delay so temperature updates at a rate 0.2 sec

    if (curtemp < 40){                             //Move on to next stage once temperature is safe to touch
      lcd.clear();                                 //Clear the screen before moving on
      refstage = 6;
    }
  }

  if (refstage == 6){                              //Reflow Run over
    lcd.setCursor(0,0);                            //Print that it is safe to touch oven and that reflow is done.
    lcd.print("Done, safe");
    digitalWrite(RelayPin,LOW);                    //Make sure oven is turned off after this point
    lcd.setCursor(1,1);

    //Convert the saved max peak values into doubles in order to perform the percent error calculation
    //Without converting to doubles, the percent error is 0
    double maxPeak1Print = maxPeak1;
    double maxPeak2Print = maxPeak2;
    double soaktempPrint = soaktemp;
    double reflowtempPrint = reflowtemp;

    //Calculate percent error and display percent error
    presoakerr = (abs((maxPeak1Print-soaktempPrint))/soaktempPrint)*100;
    lcd.print(presoakerr);
    lcd.setCursor(3,1);
    lcd.print("%");

    reflowerr = (abs((maxPeak2Print-reflowtempPrint))/reflowtempPrint)*100;
    lcd.setCursor(5,1);
    lcd.print(reflowerr);
    lcd.setCursor(7,1);
    lcd.print("%");

    delay(500);
  }

  if (curtemp > 250){                             //Software safety condition
    lcd.clear();
    digitalWrite(RelayPin,LOW);                     //Turn PID off
    lcd.setCursor(0,0);
    lcd.print("TOO HOT");
    lcd.setCursor(0,1);
    lcd.print("TURN OFF!!");                        //Prompt user to manually turn off oven
    delay(200);
  }
  return printtime;
}
