// Function that allows the user to pick a set temperature
int maxtemp;
int mintemp;

int Enter_Temp()
{
  lcd_key=read_LCD_buttons();

  if (moveon == 0){
    maxtemp = 160;
    mintemp = 140;
  }
  if (moveon == 1){
    maxtemp = 250;
    mintemp = 218;
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
  
  switch(lcd_key){


  case btnSELECT:
    {
      moveon = moveon+1;              //If moveon in the void loop is 1 then allow the user to select the set temperature
   //   lcd.setCursor(1,0);
    //  lcd.print(temp);
    lcd.clear();
      break;
    }

  case btnUP:                          //Move temperature up by one
    {
      temp = temp+1;
      normalize_number(temp);
      delay(200);
      break;
    }
  case btnDOWN:                          //Move temperature down by one
    {
      temp = temp-1;
      normalize_number(temp);
      delay(200);
      break;
    }
  case btnRIGHT:                          //Move temperature up by 10
    {
      temp = temp+10;
      normalize_number(temp);
      delay(200);
      break;
    }
  case btnLEFT:                          //Move temperature down by 10
    {
      temp = temp-10;
      normalize_number(temp);
      delay(200);
      break;
    }
  }
  return temp;
  return moveon;
}
