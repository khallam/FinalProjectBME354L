// Function that allows the user to pick a set temperature
int Enter_Temp()
{
  lcd_key=read_LCD_buttons();

  switch(lcd_key)
  {
    if (moveon == 0){
      maxtemp = 160;
      mintemp = 140;
    }
    if (moveon == 1){
      maxtemp = 250;
      mintemp = 218;
    }

  case btnSELECT:
    {
      moveon = moveon+1;              //If moveon in the void loop is 1 then allow the user to select the set temperature
      // lcd.clear();
      //  lcd.setCursor(0,0);
      // lcd.print("Enter Temp, C:");
      lcd.setCursor(1,1);
      lcd.print(temp);
      break;
    }

  case btnUP:                          //Move temperature up by one
    {
      temp = temp+1;
      if (temp > maxtemp)
      {
        //  lcd.clear();                    //Warning for low temperature
        lcd.setCursor(0,0);
        lcd.print("Lower Temp, C:");
      }
      normalize_number(temp);
      delay(500);
      break;
    }
  case btnDOWN:                          //Move temperature down by one
    {
      temp = temp-1;
      if (temp < mintemp)
      {                                             //Error if set temperature is too high. Currently, the high temperature > 25 in order to show the functionality of the device. However, this high temp
        lcd.setCursor(0,0);               //value will change according to each segment of the reflow curve.
        lcd.print("Higher Temp, C:");
      }
      normalize_number(temp);
      delay(500);
      break;
    }
  case btnRIGHT:                          //Move temperature up by 10
    {
      temp = temp+10;
      if (temp > maxtemp)
      {
        lcd.setCursor(0,0);
        lcd.print("Lower Temp, C:");
      }
      normalize_number(temp);
      delay(500);
      break;
    }
  case btnLEFT:                          //Move temperature down by 10
    {
      temp = temp-10;
      if (temp < mintemp)
      {
        lcd.setCursor(0,0);
        lcd.print("Higher Temp, C:");
      }
      normalize_number(temp);
      delay(500);
      break;
    }
  }
  return temp;
  return moveon;
}
