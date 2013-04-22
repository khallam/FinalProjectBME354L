unsigned long nowM=0;
unsigned long lastM=0;
int curTime=0;

unsigned long curMin=0;

int timeLeft=0;

int Stopwatch(int setPoint)
{
  nowM=millis()/1000;
  curTime += (nowM-lastM);
  lastM=nowM; //We did through if loop last time, better option is to update
  return curTime;
}






