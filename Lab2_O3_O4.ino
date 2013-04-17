//Lab2, Objective 3 and 4
// Temperature read in function

#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);
int lcd_key = 0;
int adc_key_in = 0;
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
#define V1 80
#define V2 230
#define V3 350
#define V4 500
#define V5 800
int temp = 23;
int cTemp = 0;
int moveon = 0;

// read the buttons function
int read_LCD_buttons()
{
  adc_key_in = analogRead(A0); // read the value from the sensor
  // my buttons when read are centered around these values: 80, 230, 350, 500, 800
  if (adc_key_in < V1 ) return btnRIGHT;
  if (adc_key_in < V2 && adc_key_in > V1) return btnUP;
  if (adc_key_in < V3 && adc_key_in > V2) return btnDOWN;
  if (adc_key_in < V4 && adc_key_in > V3) return btnLEFT;
  if (adc_key_in < V5 && adc_key_in > V4) return btnSELECT;
  if (adc_key_in > V5 ) return btnNONE;
  return btnNONE; // when all others fail, return this...
}

// Function that allows the user to pick a set temperature
int Enter_Temp()
{
  lcd_key=read_LCD_buttons();

  switch(lcd_key)
  {

  case btnSELECT:
    {
      moveon = moveon+1;              //If moveon in the void loop is 1 then allow the user to select the set temperature
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Temp, C:");
      lcd.setCursor(1,1);
      lcd.print(temp);
      break;
    }

  case btnUP:                          //Move temperature up by one
    {
      temp = temp+1;
      if (temp >25)
      {
        lcd.clear();                    //Warning for low temperature
        lcd.setCursor(0,0);
        lcd.print("Lower Temp, C:");
      }
      else if (temp >=20 && temp <=25)   
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter Temp, C:");
      }
      lcd.setCursor(1,1);
      lcd.print(temp, DEC);
      delay(500);
      break;
    }
  case btnDOWN:                          //Move temperature down by one
    {
      temp = temp-1;
      if (temp < 20)
      {
        lcd.clear();                      //Error if set temperature is too high. Currently, the high temperature > 25 in order to show the functionality of the device. However, this high temp
        lcd.setCursor(0,0);               //value will change according to each segment of the reflow curve.
        lcd.print("Higher Temp, C:");
      }
      else if (temp >=20 && temp <=25)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter Temp, C:");
      }
      lcd.setCursor(1,1);
      lcd.print(temp,DEC);
      delay(500);
      break;
    }
  case btnRIGHT:                          //Move temperature up by 10
   {
      temp = temp+10;
      if (temp > 25)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Lower Temp, C:");
      }
      else if (temp >=20 && temp <=25)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter Temp, C:");
      }
      lcd.setCursor(1,1);
      lcd.print(temp,DEC);
      delay(500);
      break;
    }
  case btnLEFT:                          //Move temperature down by 10
   {
      temp = temp-10;
      if (temp < 20)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Higher Temp, C:");
      }
      else if (temp >=20 && temp <=25)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter Temp, C:");
      }
      lcd.setCursor(1,1);
      lcd.print(temp,DEC);
      delay(500);
      break;
    }
  }
  return temp;
  return moveon;
}

//Function that reads the current input temperature
int CurrentTemp()
{
  //lcd.clear();
  cTemp = analogRead(A1);
  lcd.setCursor(0,0);
  lcd.print("Curr Temp: ");
  lcd.setCursor(11,0);
  lcd.print(cTemp);
  delay(500);                                      //This represents refresh rate. This can be increased if necessary
}

//Function that displays the set temperature chosen in the above function
int SetTempDisp()
{  
  lcd.setCursor(0,1);
  lcd.print("Set Temp:");
  lcd.setCursor(10,1);
  lcd.print(temp);
  delay(500);
}

//Code that illustrates the functionality of our functions. Look, it is very modular! All we had to do was call the functions we already made. We are beating the "noob" status!
void setup()
{
 lcd.begin(16,2);
 lcd.setCursor(0,0);
 lcd.print("Enter Temp:");
}
void loop()

{
 if (moveon == 0){
    Enter_Temp();
 }
  
  //moveon = moveon+1;
  if (moveon == 1)
  {
    CurrentTemp();
    SetTempDisp();
  }
}
