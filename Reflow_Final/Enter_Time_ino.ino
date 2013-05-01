int maxtime;
int mintime;

int Enter_Time()
{
  lcd_key=read_LCD_buttons();
  if (moveon == 3){
    maxtime = 120;
    mintime = 60;
    normalize_number(time);
  }
  if (moveon == 4){
    maxtime = 75;
    mintime = 45;
    normalize_number(time);
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
      time = time + 1;
      normalize_number(time);
      buttonLast2 = btnUP;
    }
  }
  else {
    buttonLast2 = 0;
  }

  if (lcd_key == btnRIGHT){
      time = time + 10;
      normalize_number(time);
      buttonLast3 = btnRIGHT;
      delay(200);
    }

  if (lcd_key == btnDOWN){
    if (lcd_key == btnDOWN && buttonLast4 != btnDOWN)
    {
      time = time - 1;
      normalize_number(time);
      buttonLast4 = btnDOWN;
    }
  }
  else {
    buttonLast4 = 0;
  }

  if (lcd_key == btnLEFT){
    if (lcd_key == btnLEFT && buttonLast5 != btnLEFT)
    {
      time = time - 10;
      normalize_number(time);
      buttonLast5 = btnLEFT;
    }
  }
  else {
    buttonLast5 = 0;
  }
  return time;
  return moveon;
}

