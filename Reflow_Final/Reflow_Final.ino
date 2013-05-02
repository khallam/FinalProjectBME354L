// Compiled Code for Reflow Oven

#include <LiquidCrystal.h> //Include LCD display library
LiquidCrystal lcd(8,9,4,5,6,7); //Define pins for LCD display
#include <PID_v1.h> //Include PID library
#include <EEPROM.h> //Include EEPROM library

//Variables for Reflow Input
int lcd_key = 0;
int adc_key_in = 0;

//Define buttons and voltage values for LCD
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

//Define all variables
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
int printtime;
int doneReflow=0;


void setup()
{
  lcd.begin(16,2); //Begin LCD display

}

void loop()
{
  //Read select button
  lcd_key=read_LCD_buttons();


  //User Input Stage
  if (moveon == 0){
    lcd.setCursor(0,0);
    lcd.print("Preht Temp, C");              //Input soak temperature based on Enter-Temp.INO
    Enter_Temp();
    soaktemp = temp;
    delay(5);
  }

  if (moveon == 1)                          //Moveon is controlled by Enter_Temp.INO/Enter_Time.INO and controls stage of user input
  {
    lcd.setCursor(0,0);
    lcd.print("Reflow Tem, C");
    Enter_Temp();                           //Input reflow temperature based on Enter-Temp.INO
    reflowtemp = temp;
    delay(5);
  }


  if (moveon == 2)         //Clear the screen before moving on to time input
  {
    lcd.clear();
    moveon = moveon + 1;
    delay(5);
  }

  if (moveon == 3){
    lcd.setCursor(0,0);
    lcd.print("Soak Time, sec");
    Enter_Time();                            //Input soak time based on Enter-Time.INO
    soaktime = time;
    delay(5);
  }

  if (moveon == 4){
    lcd.setCursor(0,0);
    lcd.print("Reflow Time, sec");
    Enter_Time();                            //Input reflow time based on Enter-Time.INO
    reflowtime=time;
  }
  if (moveon == 5)                           //Clear the screen once all user input is finished
  {
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    moveon = moveon+1;
    delay(200);
  }

  if (moveon == 6)                    //Display all user input 
  {
    lcd.setCursor(0,0);
    lcd.print("Sel to Start");        //Prompt user to select start if values are correct. Press reset otherwise
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
    case btnSELECT:                     //Select button moves on to start reflow
      moveon = moveon + 1;
      delay(5);
    }
  }
  if (moveon >= 7)                      //Start running the reflow curve
  {
    lcd.setCursor(0,0);                 //Clear the screen
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(8,1); 
    curTemp = analogRead(A5);           //Read current temperature
    lcd.print(curTemp);                 //Print current temperature
    lcd.setCursor(11,1);
    lcd.print("C");                     //Print units of curtemp
    lcd.setCursor(0,1);
    lcd.print(printtime,DEC);           //Print time left in stage
    lcd.setCursor(2,1);
    lcd.print("s");                     //Print units of time
    delay(500);

    stage=Reflow_Stage(curTemp, soaktemp, reflowtemp, soaktime, reflowtime);  //Run through all stages and return time left

    if (doneReflow = 1)                  //If reflow is done, record statistics
    { 
      int maxpresoaktemp;
      int presoakerror;

      maxpresoaktemp = EEPROM.read(2);              //Read EEPROM max temps and display statistics
      presoakerror = maxpresoaktemp-soaktemp;
      lcd.setCursor(0,0);
      lcd.print(maxpresoaktemp);
      lcd.setCursor(3,0);
      lcd.print(presoakerror);
    }
  }
}



