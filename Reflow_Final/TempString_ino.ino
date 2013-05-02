//Function to normalize position of temp/time as to alternate between multiple digit numbers
int normalize_number(int number)            //Define the function
{
  if (number >= 10 && number < 100){       //If two digits, add a space at the 100s digit, then  print number
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.print(number);
  }
  
  if (number >= 100 && number < 1000){         //If 3 digits, print number normally. Don't expect more than 3 digits.
    lcd.setCursor(0,1);
    lcd.print(number);

  }
  
}
