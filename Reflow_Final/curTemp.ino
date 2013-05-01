//Function that reads the current input temperature

int CurrentTemp()
 {
 lcd.clear();
 cTemp = analogRead(A1);
 lcd.setCursor(0,0);
 lcd.print("Curr Temp: ");
 lcd.setCursor(11,0);
 lcd.print(cTemp);
 delay(500);                                      //This represents refresh rate. This can be increased if necessary
 }
 
