int maxtime;
int mintime;

int Enter_Time()
{
  lcd_key=read_LCD_buttons();
  if (moveon == 3){
    maxtime = 120;
    mintime = 60;
  }
  if (moveon == 4){
    maxtime = 75;
    mintime = 45;
  }

  if (time < mintime){
    lcd.setCursor(8,1);
    lcd.print("inc time");
  }
  if (time > maxtime){
    lcd.setCursor(8,1);
    lcd.print("dec time");
  }

  if (mintime <= time && time <= maxtime){
    lcd.setCursor(8,1);
    lcd.print("        ");
  }

  switch(lcd_key)
  {

  case btnSELECT:
    {
      moveon = moveon+1;              // Allow the user to select the set time
      lcd.setCursor(1,0);
      lcd.print(time);
      break;
      lcd.clear();
    }

  case btnUP:                          //Move time up by one
    {
      time = time+1;
      normalize_number(time);
      delay(200);
      break;
    }
  case btnDOWN:                          //Move time down by one
    {
      time = time-1;
      if (time < mintime)
        normalize_number(time);
      delay(200);
      break;
    }
  case btnRIGHT:                          //Move time up by 10
    {
      time = time+10;
      normalize_number(time);
      delay(200);
      break;
    }
  case btnLEFT:                          //Move time down by 10
    {
      time = time-10;
      normalize_number(time);
      delay(200);
      break;
    }
  }
  return time;
  return moveon;
}

