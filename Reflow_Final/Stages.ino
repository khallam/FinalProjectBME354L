int refstage = 0;
int curtime;
String dispstage;
unsigned long lastM;

char Reflow_Stage(int curtemp, int soaktemp, int reflowtemp, int soaktime, int reflowtime)
{
  if (refstage == 0){
    //curTemp = ReadCurTemp();
    dispstage = "Ramp soak";
    Control(soaktemp,curtemp);                 //We need this PID function to increase the temperature to the soak temp

      if (curtemp >= soaktemp){
      refstage = 1;
      lastM=millis()/1000;
    }

    //  lcd.setCursor(6,1);
    //  lcd.print(curTemp,DEC);

    lcd.setCursor(9,0);
    lcd.print(dispstage);

    lcd.setCursor(0,1);
    lcd.print(refstage,DEC);
    delay(200);
  }

  if (refstage == 1){
    //   ReadCurTemp();
    dispstage = "Soak";
    curtime = Stopwatch(soaktime, lastM);
    lcd.setCursor(2,1);
    lcd.print(curtime);
    lcd.setCursor(9,0);
    lcd.print(dispstage);
    Control(soaktemp,curtemp);                  //We need this PID function to keep the temperature constant
    lcd.setCursor(0,1);
    lcd.print(refstage,DEC);
    delay(200);

    if (curtime >= soaktime){
      refstage = 2;
    }

    //   lcd.setCursor(6,1);
    //   lcd.print(curTemp,DEC);

    //lcd.setCursor(13,1);
    //lcd.print(refstage,DEC);
  }

  if (refstage == 2){
    // ReadCurTemp();
    dispstage = "Ramp to Reflow";

    lcd.setCursor(9,0);
    lcd.print(dispstage);

    lcd.setCursor(0,1);
    lcd.print(refstage,DEC);
    delay(200);

    Control(reflowtemp,curtemp);                //We need this PID function to increase the temperature to the reflow temp

      if (curtemp >= 217){
      refstage = 3;
      lastM=millis()/1000;
    }



    //  lcd.setCursor(6,1);
    //  lcd.print(curTemp,DEC);

    //lcd.setCursor(13,1);
    //lcd.print(refstage,DEC);
  }

  if (refstage == 3){
    // ReadCurTemp();
    dispstage = "Reflow";
    curtime = Stopwatch(reflowtime,lastM);
    lcd.setCursor(2,1);
    lcd.print(curtime);
    lcd.setCursor(9,0);
    lcd.print(dispstage);
    lcd.setCursor(0,1);
    lcd.print(refstage,DEC);
    delay(200);
    Control(reflowtemp,curtemp);

    if (curtime >= reflowtime){
      refstage = 4;
    }

    //   lcd.setCursor(6,1);
    //   lcd.print(curTemp,DEC);

  }

  if (refstage == 4){
    //  ReadCurTemp();
    dispstage = "Cooling";
    lcd.setCursor(9,0);
    lcd.print(dispstage);
    lcd.setCursor(0,1);
    lcd.print(refstage,DEC);
    delay(200);

    Control(25,curtemp);  
    
    if (curtemp < 40){
      refstage = 5;
        //Cool to room temperature
    }
    //return refstage;
  }

  if (refstage == 5){
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    refstage == 6;
  }
  
  if (refstage == 6){
    lcd.setCursor(0,0);
    lcd.print("Done");
    lcd.setCursor(0,1);
    lcd.print("Safe to touch");   
  }
}














