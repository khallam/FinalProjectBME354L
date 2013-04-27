int refstage = 0;
int curtime;

char Reflow_Stage(int curtemp, int soaktemp, int reflowtemp, int soaktime, int reflowtime)
{
  if (refstage == 0){
    //curTemp = ReadCurTemp();
    stage = 'Ramp to soak';
    Control(soaktemp,curtemp);                 //We need this PID function to increase the temperature to the soak temp

      if (curtemp >= soaktemp){
      refstage = 1;
    }

    //  lcd.setCursor(6,1);
    //  lcd.print(curTemp,DEC);

    lcd.setCursor(0,1);
    lcd.print(refstage,DEC);
    delay(200);
  }

  if (refstage == 1){
    //   ReadCurTemp();
    stage = 'Soak';
    curtime = Stopwatch(soaktime);
    Control(soaktemp,curtemp);                  //We need this PID function to keep the temperature constant
    lcd.setCursor(0,1);
    lcd.print(refstage,DEC);
    delay(200);

   
    return timeleft;

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
    stage = 'Ramp to Reflow';
    lcd.setCursor(0,1);
    lcd.print(refstage,DEC);
    delay(200);
   
    Control(reflowtemp,curtemp);                //We need this PID function to increase the temperature to the reflow temp

      if (curtemp >= 217){
      refstage = 3;
    }



    //  lcd.setCursor(6,1);
    //  lcd.print(curTemp,DEC);

    //lcd.setCursor(13,1);
    //lcd.print(refstage,DEC);
  }

  if (refstage == 3){
    // ReadCurTemp();
    stage = 'Reflow';
    curtime = Stopwatch(reflowtime);
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
    stage = 'Cooling';
        lcd.setCursor(0,1);
    lcd.print(refstage,DEC);
    delay(200);
 
    Control(25,curtemp);                         //Cool to room temperature
  }

  //   lcd.setCursor(6,1);
  //   lcd.print(curTemp,DEC);

  //lcd.setCursor(13,1);
  //lcd.print(refstage,DEC);
  return refstage;
}











