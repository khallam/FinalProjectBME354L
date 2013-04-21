//Stopwatch for Reflow Final

//Define Pin

unsigned long nowM=0;
unsigned long lastM=0;
int curtime=0;
unsigned long curMin=0;

int timeLeft=0;
//DO WE NEED ABILITY TO STOP TIME?
int stopwatch(int setPoint)
{
 // nowM=millis()/1000;
  curtime = curtime + (nowM-lastM);
  lastM=nowM; //We did through if loop last time, better option is to update

  timeLeft=setPoint-curtime;
  lcd.setCursor(0,0);
  lcd.print(timeLeft);
/*
  if (curSec > 59)
  {
    curMin=curMin+1;
    curSec=0;
  }
  lcd.setCursor(3,1);
  lcd.print(":");

  if (curSec <10)
  {
    lcd.setCursor(4,1);
    lcd.print(0);
    lcd.setCursor(5,1);
    lcd.print(curSec);
  }
  else
  {
    lcd.setCursor(4,1);
    lcd.print(curSec);
  }
  if (curMin<10)
  {
    lcd.setCursor(1,1);
    lcd.print(0);
    lcd.setCursor(2,1);
    lcd.print(curMin);
  }
  else
  {
    lcd.setCursor(1,1);
    lcd.print(curMin);
  }
  */
  return timeleft
}




