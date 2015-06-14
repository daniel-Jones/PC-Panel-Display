// this file will contain the code for my serial test program

boolean StringComplete = false; // true if the string is complete

void SerialEvent() {
	while (Serial.available()) { // when we recieve serial data
		char InChar = (char)Serial.read(); // get the incoming data
		InputString += InChar; // add this data to our string variable
		if (InChar == '\n') { // if we recieve \n, set our string as a complete string
			StringComplete = true; // set as true
			display.clearDisplay(); // clear our oled display (removes old display items)
			OledWrite(0, 1, 1, InputString); // add our text to the oled display
			RenderScene(); // render our scene
		} 
	}
}

void SerialLoop() { // this function is our programs loop function
	SerialEvent(); // check for incoming strings
	if (StringComplete) { // if the incoming string is complete
		Serial.println(InputString); // this will print our string back to the serial source
		InputString = ""; // we now empty the string variable
		StringComplete = false; // we also set our stirng to incomplete
	}
	SerialLoop(); // run our programs loop
}

void SerialSetup() { // this is our setup script for this program
	Serial.println("Connected!"); // confirm our connection by sending a string
	InputString.reserve(200); // reseve 200 bytes for the incoming string
	SerialLoop(); // run our programs loop
}
