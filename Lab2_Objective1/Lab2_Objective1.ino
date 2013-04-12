#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
int out1;
int LED=1;
boolean heatOnOff;


boolean heaterState(int setTemp){     //heater function takes an input set temperature value
  int curTemp = analogRead(A1);       //heater reads the current voltage (current temperature)
  int setTempConv = setTemp/.005;     //convert arduino bit units into celsius or voltage scale
  
  if (curTemp <= setTempConv){        //Turn heater if current temp is less than desired temp
    heatOnOff = HIGH;
    return heatOnOff;
  }
  if (curTemp > setTempConv){         //Turn heater off if current temp is greater than desired temp
    heatOnOff = LOW;
    return heatOnOff;
  }

}

// The code below demonstrates the functionality of our function

void setup(){
// pinMode(LED,OUTPUT);
}

void loop(){
  /*heatOnOff= heaterState(2);
  digitalWrite(LED, heatOnOff);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(heatOnOff);
  delay(200);
  */
} 




