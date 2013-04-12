#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);


boolean heaterState(int setTemp){ //heater function takes an input temperature value
  int curTemp = analogRead(A1);
  
  if (curTemp < setTemp){
    
  }
  
  boolean heatOnOff = 
}

int heater = 13;
int setTemp; // User defines the setpoint

void setup(){

}

void loop(){
  int curTemp = analogRead(A1);
  delay(200);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(curTemp,DEC);
  
}



