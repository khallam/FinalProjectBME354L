//Function to normalize position of temp/time as to alternate between multiple digit numbers

int normalize_number(int number, int pos1, int pos2)            //Define the function
{
  if (number >= 10 && number < 100){       //If 2 digits, add a space at the 100s digit, then  print number
    lcd.setCursor(pos1,pos2);
    lcd.print(" ");
    lcd.print(number);
  }
  if (number >= 100 && number < 1000){         //If 3 digits, print number normally. Don't expect more than 3 digits.
    lcd.setCursor(pos1,pos2);
    lcd.print(number);
  }
  if (number<10){                         //If 1 digits, print two spaces followed by the digit
    lcd.setCursor(pos1,pos2);
    lcd.print("  ");
    lcd.print(number);
  }
}
