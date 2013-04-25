//Adapted from Dr. Mark Palmeri--4/21/2013
int buttonPin=A0;
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

int read_LCD_buttons()
{
  int adcIn;
  adcIn = analogRead(buttonPin);
  delay(5); 
  if (adcIn < 50) return btnRIGHT;
  else if (adcIn < 195) return btnUP;
  else if (adcIn < 380) return btnDOWN;
  else if (adcIn < 555) return btnLEFT;
  else if (adcIn < 790) return btnSELECT;
  else return btnNONE;
}
