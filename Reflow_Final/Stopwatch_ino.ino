unsigned long nowM=0;
int curTime=0;


int timeLeft=0;

int Stopwatch(int setPoint,unsigned long lastM)
{
  nowM=millis();
  curTime =(nowM-lastM)/1000;
  //lastM=nowM; //We did through if loop last time, better option is to update
 // lcd.setCursor(2,1);
//  lcd.print(curTime);
  return curTime;
}






