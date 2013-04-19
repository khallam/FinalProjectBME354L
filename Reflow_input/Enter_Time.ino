int maxtime;
int mintime;
int time;

int Enter_Time()
{
  lcd_key=read_LCD_buttons();

  switch(lcd_key)
  {
    if (moveon == 3){
       maxtime = 120;
       mintime = 60;
    }
    if (moveon == 4){
        maxtime = 75;
        mintime = 45;
    }

  case btnSELECT:
    {
      moveon = moveon+1;              // Allow the user to select the set time
      lcd.setCursor(1,1);
      lcd.print(time);
      break;
    }

  case btnUP:                          //Move time up by one
    {
      time = time+1;
      if (time > maxtime)
      {
        //  lcd.clear();                    //Warning for low time
        lcd.setCursor(0,0);
        lcd.print("Decrease time, s");
      }
      normalize_number(time);
      delay(500);
      break;
    }
  case btnDOWN:                          //Move time down by one
    {
      time = time-1;
      if (time < mintime)
      {                                             //Error if set time is too high. Currently, the high time > 25 in order to show the functionality of the device. However, this high time
        lcd.setCursor(0,0);               //value will change according to each segment of the reflow curve.
        lcd.print("Increase time, s");
      }
      normalize_number(time);
      delay(500);
      break;
    }
  case btnRIGHT:                          //Move time up by 10
    {
      time = time+10;
      if (time > maxtime)
      {
        lcd.setCursor(0,0);
        lcd.print("Decrease time, s");
      }
      normalize_number(time);
      delay(500);
      break;
    }
  case btnLEFT:                          //Move time down by 10
    {
      time = time-10;
      if (time < mintime)
      {
        lcd.setCursor(0,0);
        lcd.print("Increase time, s");
      }
      normalize_number(time);
      delay(500);
      break;
    }
  }
  return time;
  return moveon;
}
