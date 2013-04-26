// Function that allows the user to pick a set temperature
int maxtemp;
int mintemp;
int buttonLast1=0;
int buttonLast2=0;
int buttonLast3=0;
int buttonLast4=0;
int buttonLast5=0;

int Enter_Temp()
{
  lcd_key=read_LCD_buttons();

  if (moveon == 0){
    maxtemp = 160;
    mintemp = 140;
    lcd.setCursor(0,1);
    lcd.print(temp);
  }
  if (moveon == 1){
    maxtemp = 250;
    mintemp = 218;
    lcd.setCursor(0,1);
    lcd.print(temp);
  }

  if (temp < mintemp){
    lcd.setCursor(8,1);
    lcd.print("too low");
  }
  if (temp > maxtemp){
    lcd.setCursor(8,1);
    lcd.print("too high");
  }
  
  if (mintemp <= temp && temp <= maxtemp){
    lcd.setCursor(8,1);
    lcd.print("        ");
  }
  
  
   if (lcd_key == btnSELECT){
    if (lcd_key == btnSELECT && buttonLast1 != btnSELECT)
    {
      moveon = moveon + 1;
      lcd.clear();
      buttonLast1 = btnSELECT;
    }
  }
  else{
    buttonLast1 = 0;
  }


  if (lcd_key == btnUP){
    if (lcd_key == btnUP && buttonLast2 != btnUP)
    {
      temp = temp + 1;
      normalize_number(temp);
      buttonLast2 = btnUP;
    }
  }
  else {
    buttonLast2 = 0;
  }

  if (lcd_key == btnRIGHT){
      temp = temp + 10;
      normalize_number(temp);
      buttonLast3 = btnRIGHT;
      delay(200);
    }

  if (lcd_key == btnDOWN){
    if (lcd_key == btnDOWN && buttonLast4 != btnDOWN)
    {
      temp = temp - 1;
      normalize_number(temp);
      buttonLast4 = btnDOWN;
    }
  }
  else {
    buttonLast4 = 0;
  }

  if (lcd_key == btnLEFT){
    if (lcd_key == btnLEFT && buttonLast5 != btnLEFT)
    {
      temp = temp - 10;
      normalize_number(temp);
      buttonLast5 = btnLEFT;
    }
  }
  else {
    buttonLast5 = 0;
  }

  return temp;
  return moveon;
}
