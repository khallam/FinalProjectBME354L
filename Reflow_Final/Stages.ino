int refstage = 0;
int curtime;
String dispstage;
unsigned long lastM;

char Reflow_Stage(int curtemp, int soaktemp, int reflowtemp, int soaktime, int reflowtime)
{
  if (refstage == 0){
    lastM = millis();
    refstage = 1;
  }

  if (refstage == 1){
    //curTemp = ReadCurTemp();
    dispstage = "Presoak";
    Control(soaktemp,curtemp,lastM);                 //We need this PID function to increase the temperature to the soak temp

    if (curtemp >= soaktemp){
      refstage = 2;
      lastM=millis();
    }

    lcd.setCursor(3,0);
    lcd.print(dispstage);
    delay(500);
  }

  if (refstage == 2){
    dispstage = "Soak";
    curtime = Stopwatch(soaktime, lastM);
    printtime = soaktime-curtime;
    lcd.setCursor(3,0);
    lcd.print(dispstage);
    Control(soaktemp,curtemp,lastM);                  //We need this PID function to keep the temperature constant
    delay(500);

    if (curtime >= soaktime){
      refstage = 3;
    }
  }

  if (refstage == 3){
    dispstage = "PreRef";

    lcd.setCursor(3,0);
    lcd.print(dispstage);
    delay(500);

    Control(reflowtemp,curtemp,lastM);                //We need this PID function to increase the temperature to the reflow temp

    if (curtemp >= 217){
      refstage = 4;
      lastM=millis();
    }
  }

  if (refstage == 4){
    dispstage = "Reflow";
    curtime = Stopwatch(reflowtime,lastM);
    lcd.setCursor(0,1);
    lcd.print(reflowtime-curtime);
    lcd.setCursor(2,1);
    lcd.print("s");
    lcd.setCursor(3,0);
    lcd.print(dispstage);
    delay(500);
    Control(reflowtemp,curtemp,lastM);


    if (curtime >= reflowtime){
      refstage = 5;
    }
  }

  if (refstage == 5){
    dispstage = "Cooling";
    lcd.setCursor(3,0);
    lcd.print(dispstage);
    delay(500);

    Control(25,curtemp,lastM);  

    if (curtemp < 40){
      refstage = 6;
      //Cool to room temperature
    }
  }

  if (refstage == 6){
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    refstage == 7;
  }

  if (refstage == 7){
    lcd.setCursor(0,0);
    lcd.print("Done");
    lcd.setCursor(0,1);
    lcd.print("Safe to touch");   
  }

  if (curtemp > 250){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TOO HOT");
    lcd.setCursor(0,1);
    lcd.print("TURN OFF!!");
  }
  return printtime;
}
















