int refstage = 0;
char stage;

char Reflow_Stage(int curtemp, int soaktemp, int reflowtemp, int curtime, int soaktime, int reflowtime)
{
  if (refstage == 0){
    stage = 'Ramp to soak';
   // myPID();
    
    if (curtemp >= soaktemp){
      refstage = 1;
    }
  }
  
  if (refstage == 1){
    stage = 'Soak';
  //  myPID();
  timeleft=stopwatch(soaktime);
    
    if (curtime >= soaktime){
      refstage = 2;
    }
  }
  
  if (refstage == 2){
    stage = 'Ramp to Reflow';
   // myPID();
    
    if (curtemp >= 217){
      refstage = 3;
    }
  }
  
  if (refstage == 3){
    stage = 'Reflow';
    //myPID();
    
    if (curtime >= reflowtime){
     refstage = 4;
    }
  }

if (refstage == 4){
  stage = 'Cooling';
  //myPID();
}

return stage;

  
  
 
 

