//Function to allow user to input time

int maxtime;
int mintime;

int Enter_Time()                         //Function to enter soak and reflow time
{
  lcd_key=read_LCD_buttons();           //Call button read function
  if (moveon == 3){                    //Define optimal time ranges for SOAK stage
    maxtime = 120;
    mintime = 60;
    normalize_number(time,0,1);            //Call the TempString.INO function to displace correctly
  }
  if (moveon == 4){                    //Define optimal time ranges for REFLOW stage
    maxtime = 75;
    mintime = 45;
    normalize_number(time,0,1);            //Normalize for correct printing like above
  }

  if (time < mintime){                 //Prompt user to increase set time if too low
    lcd.setCursor(8,1);
    lcd.print("inc time");
  }
  if (time > maxtime){                 //Prompt user to decrease set time if too high
    lcd.setCursor(8,1);
    lcd.print("dec time");
  }

  if (mintime <= time && time <= maxtime){   //Reset warning message 
    lcd.setCursor(8,1);
    lcd.print("        ");
  }

  
   if (lcd_key == btnSELECT){                                        //Select button moves on to next stage in Reflow_Final.INO
    if (lcd_key == btnSELECT && buttonLast1 != btnSELECT)            //Debounce function select button
    {
      moveon = moveon + 1;
      lcd.clear();
      buttonLast1 = btnSELECT;
    }
  }
  else{
    buttonLast1 = 0;
  }


  if (lcd_key == btnUP){                                 //Button up increase time by 1
    if (lcd_key == btnUP && buttonLast2 != btnUP)        //Debounce for button up
    {
      time = time + 1;
      normalize_number(time,0,1);
      buttonLast2 = btnUP;
    }
  }
  else {
    buttonLast2 = 0;
  }

  if (lcd_key == btnRIGHT){                             //Button right increase time by 10                              
      time = time + 10;                                 //No debounce allows for a speedy increase of set values, works as well as debounce
      normalize_number(time,0,1);
      buttonLast3 = btnRIGHT;
      delay(200);
    }

  if (lcd_key == btnDOWN){                             //Button down decreases time by 1    
    if (lcd_key == btnDOWN && buttonLast4 != btnDOWN)  //debounce for button down
    {
      time = time - 1;
      normalize_number(time,0,1);
      buttonLast4 = btnDOWN;
    }
  }
  else {
    buttonLast4 = 0;
  }

  if (lcd_key == btnLEFT){                             //Button left decreases time by 10  
    if (lcd_key == btnLEFT && buttonLast5 != btnLEFT)  //Debounce for button left
    {
      time = time - 10;
      normalize_number(time,0,1);
      buttonLast5 = btnLEFT;
    }
  }
  else {
    buttonLast5 = 0;
  }
  return time;           //Return user-inputed time
  return moveon;         //Update moveon in the case that the select button was pressed
}
