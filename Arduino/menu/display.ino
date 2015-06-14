// These functions control the lcd/oled display
void LcdWrite(int x, int y, String text) { // this function will write to the lcd screen, this is not handled by RenderScene()
	lcd.setCursor(x, y); // set our lcd cursor position
	lcd.print(text); // write to the lcd screen
}

void OledWrite(int x, int y, int size, String text) { // this function will write to our oled
	display.setTextSize(size); // set the font size
	display.setTextColor(WHITE); // set the font color
	display.setCursor(x, y); // set the cursor position
	display.println(text); // add our text to the oled buffer
}

void RenderScene() { // this function will render our scene on the oled display
	display.display(); // update our oled (print buffer)
}
