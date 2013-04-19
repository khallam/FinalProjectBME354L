int normalize_number(int number)
{
  if (number >= 10 && number < 100){
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.print(number);
  }
  
  if (number >= 100 && number < 1000){
    lcd.setCursor(0,1);
    lcd.print(number);
  }
  
}

