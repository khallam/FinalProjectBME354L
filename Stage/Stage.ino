#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);

int temp_set1;        //Delete this later because temp_set will come from reflow input function
int curtemp;            //Delete this later because temp will come from cur temp function
int temp_setpk;
int timer;
int time_soak;
int reflowtime;
char stage;

char Reflow_Stage()
{
  if (curtemp < temp_set1){
    stage = 'Ramp to soak';
  }
  
  if (timer > 0 && timer < timesoak){  //if (curtemp > temp_set - 20 && curtemp < temp_set + 20){
    stage = 'Soak';
    //Add the timer function here?
  }
  
  //if (curtemp < temp_setpk && curtemp > temp_set1 ){
   if (timer > time_soak && temp < temp_setpk){
    stage = 'Ramp to Reflow';
  }
  
  if (curtemp > 217 && curtemp < temp_setpk){
    stage = 'Reflow';
  }
  
  if (timer > reflow time){
    stage = 'Cooling';
  }
}


void setup(){
  lcd.begin(16,2);
}

void loop(){
  lcd.setCursor(0,0);
  lcd.print(stage, char);
  
}
