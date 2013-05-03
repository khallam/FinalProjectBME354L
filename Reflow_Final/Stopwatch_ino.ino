//Function to measure time left

unsigned long nowM=0;
int curTime=0;
int timeLeft=0;

int Stopwatch(int setPoint,unsigned long lastM) //Function to count time
{
  nowM=millis(); //Current millis values (since program started running)
  curTime =(nowM-lastM)/1000; //Find time based on a 'zeroed' time--lastM is in STAGEES.INO
  return curTime;
}
