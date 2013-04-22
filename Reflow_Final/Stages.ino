int refstage = 0;
int curtime;

char Reflow_Stage(int curtemp, int soaktemp, int reflowtemp, int soaktime, int reflowtime)
{
  if (refstage == 0){
    stage = 'Ramp to soak';
    Control(soaktemp);                 //We need this PID function to increase the temperature to the soak temp
    
    if (curtemp >= soaktemp){
      refstage = 1;
    }
  }
  
  if (refstage == 1){
    stage = 'Soak';
    curtime = Stopwatch(soaktime);
    Control(soaktemp);                  //We need this PID function to keep the temperature constant
    return timeleft;
    if (curtime >= soaktime){
      refstage = 2;
    }
  }
  
  if (refstage == 2){
    stage = 'Ramp to Reflow';
    Control(reflowtemp);                //We need this PID function to increase the temperature to the reflow temp
    
    if (curtemp >= 217){
      refstage = 3;
    }
  }
  
  if (refstage == 3){
    stage = 'Reflow';
    curtime = Stopwatch(reflowtime);
    Control(reflowtemp);
    
    if (curtime >= reflowtime){
     refstage = 4;
    }
  }

if (refstage == 4){
  stage = 'Cooling';
  Control(25);                         //Cool to room temperature
}
return stage;
}

  
  
 
 

