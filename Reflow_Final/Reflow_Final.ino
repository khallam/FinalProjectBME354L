// Compiled Code for Reflow Oven

#include <LiquidCrystal.h> //Include LCD display library
LiquidCrystal lcd(8,9,4,5,6,7); //Define pins for LCD display
#include <PID_v1.h> //Include PID library
#include <EEPROM.h> //Include EEPROM library

//Variables for Reflow Input
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

int cTemp = 0;
int moveon = 0;
double soaktemp;
double reflowtemp;
int temp=150;
int time=60;
int reflowtime;
int soaktime;
int timeleft;
char stage;
//int nowM;
int curTemp;


void setup()
{
  lcd.begin(16,2);

}

void loop()
{
  //Read select button
  lcd_key=read_LCD_buttons();


  //User Input Stage
  if (moveon == 0){
    lcd.setCursor(0,0);
    lcd.print("Preht Temp, C");
    Enter_Temp();
    soaktemp = temp;
    delay(200);
  }

  if (moveon == 1)
  {
    lcd.setCursor(0,0);
    lcd.print("Reflow Tem, C");
    Enter_Temp();
    reflowtemp = temp;
    delay(200);
  }


  if (moveon == 2)
  {
    lcd.clear();
    moveon = moveon + 1;
    delay(200);
  }

  if (moveon == 3){
    lcd.setCursor(0,0);
    lcd.print("Soak Time, sec");
    Enter_Time();
    soaktime = time;
    delay(200);
  }

  if (moveon == 4){
    lcd.setCursor(0,0);
    lcd.print("Reflow Time, sec");
    Enter_Time();
    reflowtime=time;
  }
  //END OF USER INPUT
  //Is user sure?
  if (moveon == 5) 
  {
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    moveon = moveon+1;
    delay(200);
  }

  if (moveon == 6)
  {
    lcd.setCursor(0,0);
    lcd.print("Sel to Start");
    lcd.setCursor(0,1);
    lcd.print(soaktemp);
    lcd.setCursor(4,1);
    lcd.print(reflowtemp);
    lcd.setCursor(8,1);
    lcd.print(soaktime);
    lcd.setCursor(12,1);
    lcd.print(reflowtime);
    lcd_key=read_LCD_buttons();
    switch(lcd_key){
    case btnSELECT:
      moveon = moveon + 1;
      delay(200);
    }
    lcd.setCursor(15,1);
    lcd.print(moveon);
  }
  if (moveon >= 7)
  {
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    //curTemp = ReadCurTemp();
    lcd.setCursor(0,0);
    lcd.print("starting");

    //curTemp = ReadCurTemp();

    lcd.setCursor(12,1);
    lcd.print(moveon,DEC);
    //curTemp = ReadCurTemp();

    lcd.setCursor(8,1); 
    curTemp = analogRead(A5);
    lcd.print(curTemp);
    delay(500);

    stage=Reflow_Stage(curTemp, soaktemp, reflowtemp, soaktime, reflowtime);

    //  lcd.setCursor(14,1);
    //  lcd.print(refstage);

    /* curTemp = ReadCurTemp();
     lcd.setCursor(6,1);
     lcd.print(curTemp,DEC);
     //delay(200);
     
     //Time Count
     //nowM=millis()/1000;
     */

  }

}















