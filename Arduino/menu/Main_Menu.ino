// some ints and variables for this tab
int ItemCount = 6; // stores how many menu items we have
int xPos = 0; // this holds our starting point for the x axis of our menu items
int yPos = 35; // the starting point of our menu items
int yGain = 10; // how many positions each item will be seperated

void Items() { // this functions will display our items on screen
	// more than 6 items will break everything!
	String ItemList[] = {"Bird", "Gravity", "Song", "Text", "Weather", "Who"}; // our menu items
	// our ItemList[] will contain ItemCount index values - ie you have a menu value
	// so, in theory we can run a loop that will automate displaying items
	for (int x = - 1; x < ItemCount - 1; x++) { // this will run through each item in ItemList[]
		OledWrite(xPos, yPos, 1, ItemList[x + 1]); // put our menu items into the oled buffer
		yPos += yGain; // add yGain to our yPos
		if (yPos > 60) { // if we hit the bottom of the screen, move our cursor to a new point
			if (xPos == 0) { // if the first column is full
				xPos = 60; // change our x position
			} else if (xPos == 60) { // if the second column is full
				xPos = 0; // change our x position
			}
			yPos = 35; // reset our y position
		}
	}
}

void MenuDisplay() { // this function controls our main menu
	OledWrite(10, 10, 1, "System Menu"); // write our title to the oled buffer
	display.drawLine(0, 30, 128, 30, WHITE); // draw a line under our title | x1, y1, x2, y2
	Items(); // display our items on screen
}

int CursorxPos = 0; // our cursors starting x position
int CursoryPos = 35; // our cursors starting y position
String Cursor = "<"; // this string holds our cursors image

void Selection() { // this function will control our buttons in the menu
        
	ButtonUp = digitalRead(ButtonUpPin); // up button state
	ButtonLeft = digitalRead(ButtonLeftPin); // left button state
	ButtonRight = digitalRead(ButtonRightPin); // right button state
        if (irrecv.decode(&results)) {
                unsigned int value = results.value; // recieve IR information
                switch(value) {
                        case Enter:
                          ButtonUp = HIGH;
                          break;
                        case Up:
                          ButtonRight = HIGH;
                          break;
                        case Down:
                          ButtonLeft = HIGH;
                          break;
                        case Off:
                          asm volatile ("  jmp 0");  
                          break;
        }
        irrecv.resume(); // Receive the next value
        }
        
	if (ButtonLeft == HIGH) { // left button detection - up
		CursoryPos += yGain; // add yGain to our cursors y position
		display.clearDisplay(); // clear our oled buffer, this removes ghosting
		MenuDisplay(); // therefore, we need display Items() again
		delay(100); // delay a little, this stops fast scrolling
	}
	if (ButtonRight == HIGH) { // right button detection - down
		CursoryPos -= yGain; // take yGain away from our cursors y position
		display.clearDisplay(); // clear our oled buffer, this removes ghosting
		MenuDisplay(); // therefore, we need display MenuDisplay() again
		delay(100); // delay a little, this stops fast scrolling
	} 
	if (CursorxPos == 0 && CursoryPos > 60) { // if we reach the end of the first row, move the cursor to the second row
		CursorxPos = 50; // change our cursors x position
		CursoryPos = 35; // reset our y position
	}
	if (CursorxPos == 50 && CursoryPos > 60) { // if we reach the end of the first row, move the cursor to the second row
		CursorxPos = 0; // change our cursors x position
		CursoryPos = 35; // reset our y position
	}
	if (CursorxPos == 50 && CursoryPos == 25) { // if the cursor is going backwards, towards the first row, change the cursors position
		CursorxPos = 0; // change our cursors x position
		CursoryPos = 55; // change our cursors y position
	}
	if (CursorxPos == 0 && CursoryPos == 25) { // if the cursor is going backwards, towards the first row, change the cursors position
		CursorxPos = 50; // change our cursors x position
		CursoryPos = 55; // change our cursors y position
	}

	// now we will detect what has actually been pressed, and act upon it accordingly
	if (ButtonUp == HIGH) { // the middle button was pressed
		if (CursorxPos == 0 && CursoryPos == 35) { // the first menu item was selected
			lcd.clear(); // clear the lcd display
			LcdWrite(0, 0, "Flappy Asterisk"); // write the items name to the lcd display
			GameState = 1; // tell the script Flappy Asterisk is running
			FlappyAsteriskSetup(); // start this particular game
		}
		if (CursorxPos == 0 && CursoryPos == 45) { // the second menu item was selected
			lcd.clear(); // clear the lcd display
			LcdWrite(0, 0, "Gravity"); // write the items name to the lcd display
			GameState = 2; // tell the script gravity tests is running
			GravitySetup(); // start this particular game
		}
		if (CursorxPos == 0 && CursoryPos == 55) { // the third menu item was selected
			lcd.clear(); // clear the lcd display
			LcdWrite(0, 0, "It's Mario!"); // write the items name to the lcd display
			GameState = 2; // tell the script mario is running
			Mario(); // start this particular game
		}
                if (CursorxPos > 0 && CursoryPos == 35) { // the third menu item was selected
			lcd.clear(); // clear the lcd display
			LcdWrite(0, 0, "Text"); // write the items name to the lcd display
			GameState = 2; // tell the script mario is running
			SerialSetup(); // start this particular game
		}
                if (CursorxPos > 0 && CursoryPos == 45) { // the third menu item was selected
			lcd.clear(); // clear the lcd display
			LcdWrite(0, 0, "Weather"); // write the items name to the lcd display
			GameState = 2; // disable menu
			CurrentWeatherLoop(); // weather script
		}
                if (CursorxPos > 0 && CursoryPos == 55) { // the third menu item was selected
			lcd.clear(); // clear the lcd display
			LcdWrite(0, 0, "Made By:"); // write the items to the lcd display
                        LcdWrite(0, 1, "Daniel Jones"); // write the items to the lcd display
		}
	}
	OledWrite(CursorxPos + 40, CursoryPos, 1, Cursor); // add our cursor to the oled buffer
}

/* to do: 
fix the menu if less one row of items exist?
*/
