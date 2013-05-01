unsigned long nowM=0;
int curTime=0;


int timeLeft=0;

int Stopwatch(int setPoint,unsigned long lastM)
{
  nowM=millis();
  curTime =(nowM-lastM)/1000;
  return curTime;
}






