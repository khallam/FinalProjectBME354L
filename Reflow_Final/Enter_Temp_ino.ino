// Function that allows the user to pick a set temperature

//Define Variables
int maxtemp;
int mintemp;
int buttonLast1=0;
int buttonLast2=0;
int buttonLast3=0;
int buttonLast4=0;
int buttonLast5=0;

int Enter_Temp()                   //Define the function for user input temperature
{
  lcd_key=read_LCD_buttons();      //Call the read buttons function

  if (moveon == 0){                //Moveon is based on Reflow_Final.INO
    maxtemp = 160;                 //Define safe temperature ranges for SOAK stage
    mintemp = 140;
    lcd.setCursor(0,1);            
    lcd.print(temp);
  }
  if (moveon == 1){               
    maxtemp = 250;                 //Define safe temperature ranges for REFLOW stage
    mintemp = 218;
    lcd.setCursor(0,1);
    lcd.print(temp);
  }

  if (temp < mintemp){             //Prompt user to enter a higher temperature
    lcd.setCursor(8,1);
    lcd.print("too low");
  }
  if (temp > maxtemp){             //Prompt user to enter a lower temperature
    lcd.setCursor(8,1);
    lcd.print("too high");
  }

  if (mintemp <= temp && temp <= maxtemp){             //Reset screen to delete prompt for lower/higher temp
    lcd.setCursor(8,1);
    lcd.print("        ");
  }

   if (lcd_key == btnSELECT){                          //Debounce function
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


  if (lcd_key == btnUP){                              //Define button up to increase temperature by 1
    if (lcd_key == btnUP && buttonLast2 != btnUP)     //Debounce for button up
    {
      temp = temp + 1;
      normalize_number(temp);
      buttonLast2 = btnUP;
    }
  }
  else {
    buttonLast2 = 0;
  }

  if (lcd_key == btnRIGHT){                            //Define button right to increase temperature by 10          
      temp = temp + 10;
      normalize_number(temp);
      buttonLast3 = btnRIGHT;
      delay(200);
    }

  if (lcd_key == btnDOWN){                             //Define button down to decrease temperature by 1   
    if (lcd_key == btnDOWN && buttonLast4 != btnDOWN)  //Debounce function for button down
    {
      temp = temp - 1;
      normalize_number(temp);
      buttonLast4 = btnDOWN;
    }
  }
  else {
    buttonLast4 = 0;
  }

  if (lcd_key == btnLEFT){                                  //Define button left to decrease temperature by 10   
    if (lcd_key == btnLEFT && buttonLast5 != btnLEFT)       //Debounce function for button left
    {
      temp = temp - 10;
      normalize_number(temp);
      buttonLast5 = btnLEFT;
    }
  }
  else {
    buttonLast5 = 0;
  }

  return temp;                                             //Return the user-set temperature
  return moveon;                                           //Return moveon
}
