//Adapted from Dr. Mark Palmeri--4/21/2013
int buttonPin=A0;                                 //Read Pin A0
#define btnRIGHT 0  //Define buttons
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

int read_LCD_buttons()            //Function statement to read buttons
{
  int adcIn;
  adcIn = analogRead(buttonPin);               //Read button pin A0
  delay(5); 
  if (adcIn < 50) return btnRIGHT;            //Conditions of voltage divider to obtain each button value
  else if (adcIn < 195) return btnUP;
  else if (adcIn < 380) return btnDOWN;
  else if (adcIn < 555) return btnLEFT;
  else if (adcIn < 790) return btnSELECT;
  else return btnNONE;
}
