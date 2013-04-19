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
int preheattemp;
int reflowtemp;
int maxtemp;
int mintemp;

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

//Function that reads the current input temperature
/*
int CurrentTemp()
 {
 lcd.clear();
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
 */

//Code that illustrates the functionality of our functions. Look, it is very modular! All we had to do was call the functions we already made. We are beating the "noob" status!
void setup()
{
  lcd.begin(16,2);
}
void loop()

{
  if (moveon == 0){
    lcd.setCursor(0,0);
    lcd.print("Preheat Temp");
    Enter_Temp();
    preheattemp = temp;
    delay(200);
  }

  if (moveon == 1)
  {
    lcd.setCursor(0,0);
    lcd.print("Reflow Temp");
    Enter_Temp();
    reflowtemp = temp;
    delay(200);
  }

  if (moveon == 2)
  {
    Enter_Temp();
    lcd.clear();
    delay(200);
  }

  if (moveon == 3){
    lcd.setCursor(0,0);
    lcd.print("Soak Time");
    Enter_Time();
    lcd.clear();
    delay(200);
  }
    if (moveon == 4){
      lcd.setCursor(0,0);
      lcd.print("Reflow Time");
      Enter_Time();

    }
  
  

}


