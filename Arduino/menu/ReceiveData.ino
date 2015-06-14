// here we will setup and collect our serial data

void ReceiveData() {
  while (Serial.available()) { // when we recieve serial data
    char InChar = (char)Serial.read(); // get the incoming data
    InputString += InChar; // add this data to our string variable
    if (InChar == '#') { // if we recieve \n, print
      lcd.clear();
      LcdWrite(0, 0, InputString.substring(0, InputString.length() - 1)); // add our text to the lcd display
      LcdWrite(0, 1, InputString.substring(0, InputString.length() - 1).substring(16)); // add our text to the lcd display      
      RenderScene(); // render
      InputString = "";
      break;
    }
    if (InChar == '\n') { // if we recieve \n, print
      display.clearDisplay(); // clear our oled display (removes old display items)
      OledWrite(0, 1, 1, InputString); // add our text to the oled display
      RenderScene(); // render
      InputString = "";
    } 
  }
}
