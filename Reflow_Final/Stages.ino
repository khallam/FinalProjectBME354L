int refstage = 0; //Constant to control progress of stages
int curtime; //from STOPWATCH.INO
String dispstage;
unsigned long lastM;
int maxPeak=0;

char Reflow_Stage(int curtemp, int soaktemp, int reflowtemp, int soaktime, int reflowtime) //Function to run through all stages--Used in REFLOW_FINAL.INO
{
  if (refstage == 0){ //This stage simply records time to reach this point, and freezes lastM
    lastM = millis();
    refstage = 1; //run and move on to Pre-Soak
  }

  if (refstage == 1){                              //Pre-Soak stage--dependent upon temperature condition
    dispstage = "Presoak";
    Control(soaktemp,curtemp,lastM);               //PID function modulates temp to soaktemp 

    if (curtemp >= soaktemp){                      //Condition to move on to soak stage
      refstage = 2;
      lastM=millis();                              //Freeze millis time as lastM
    }

    lcd.setCursor(3,0);
    lcd.print(dispstage);
    delay(500);                                    //Take measurements every 0.5 seconds
  }

  if (refstage == 2){                              //Soak stage--dependent upon time condition
    dispstage = "Soak";
    curtime = Stopwatch(soaktime, lastM);          //Record current time based on lastM
    printtime = soaktime-curtime;                  //Time left in the stage
    lcd.setCursor(3,0);
    lcd.print(dispstage);                          //Print current stage
    Control(soaktemp,curtemp,lastM);               //PID functions keeps temp at soaktemp
    delay(500);                                    //Delay 0.5 seconds between measurements

    if (maxPeak <= curTemp){
      maxPeak = curTemp;
    }
    else if (maxPeak>curTemp){
      maxPeak = maxPeak;
      EEPROM.write(1,maxPeak);
    }

    if (curtime >= soaktime){                      //Time condition to move on to pre-reflow
      refstage = 3;
    }
  }

  if (refstage == 3){                              //Pre-Reflow Stage--Dependent upon temperature condition 
    dispstage = "PreRef";
    lcd.setCursor(3,0);
    lcd.print(dispstage);                          //Print current stage
    delay(500);                                    //Delay 0.5 seconds between measurements

    Control(reflowtemp,curtemp,lastM);             //This PID ramps up until the temperature reaches reflow temp

    if (curtemp >= 217){                           //Condition to move on to reflow temp --NOT user input (Reflow starts at 217 C)
      refstage = 4;
      lastM=millis();                              //Freeze millis as lastM
    }
  }

  if (refstage == 4){                              //Reflow Stage--Time dependent
    dispstage = "Reflow";
    curtime = Stopwatch(reflowtime,lastM);         //Current time based on zeroed time
    printtime=reflowtime-curtime;                 //Display time left

    lcd.setCursor(3,0);
    lcd.print(dispstage);                          //Display current stage
    delay(500);                                    //Delay 0.5 seconds between measurements

    if (maxPeak <= curTemp){
      maxPeak = curTemp;
    }
    else if (maxPeak>curTemp){
      maxPeak = maxPeak;
      EEPROM.write(2,maxPeak);
    }

    Control(reflowtemp,curtemp,lastM);             //PID function to keep temp at reflow temp

    if (curtime >= reflowtime){                    //Condition to move on to cooling stage
      refstage = 5;
    }
  }

  if (refstage == 5){                              //Cooling stage--Dependent on temperature
    dispstage = "Cooling (FAN ON)";
    lcd.setCursor(3,0);
    lcd.print(dispstage);                          //Display stage
    delay(500);                                    //Delay 0.5 seconds before each sample

    Control(25,curtemp,lastM);                     //PID controls temperature at room temperature

    if (curtemp < 40){                             //Move on to next stage once temperature is safe to touch
      refstage = 6;
    }
  }

  if (refstage == 6){                              //Clear the screen
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    refstage == 7;
  }

  if (refstage == 7){                              //Reflow Run over
    lcd.setCursor(0,0);
    lcd.print("Done");
    lcd.setCursor(0,1);
    lcd.print("Safe to touch"); 
    doneReflow=1;  
  }

  if (curtemp > 250){                             //Software safety condition
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TOO HOT");
    lcd.setCursor(0,1);
    lcd.print("TURN OFF!!");
  }
  return printtime;
}

