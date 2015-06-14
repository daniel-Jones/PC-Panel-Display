// this tab will contain our flappy asterisk game

#define OLED_RESET 4 // oled reset code
int Score = 0; // our scores variable
int HighScoreCount = 0; // our high score variable
int ScoreLock = 0; // locks our score counter
int Pause = 1; // when set to one, the game is practically Paused

// lets create some functions
void DrawScore(int Add) { // this function will draw our score to screen
	Score = Score + Add; // add to our score
	OledWrite(100, 5, 1, String(Score)); // put our score into the oled buffer
}

// our platform arrays
int Platform1[] = {0, 63, 128, 63}; // x1, y1, x2, y2
int Pipe1[] = {128, 63, 128, 40}; // our first pipe
int PipeSpeed = 4; // our pipes speed
int Pos[] = {0, 0}; // this will hold our pipes new x position
void DrawPlatforms() { // this function will add our platforms to the oled buffer
	/*
	Lets go into a little detail in this function:
	We use the drawLine() function to draw a line to the oled.
	the arguments are as follows:
	x1, y1, x2, y2, color
	Lets think of using a pen.
	x1 = the starting x position of the pens tip
	y1 = the starting y position of the pens tip
	x2 = the ending x position of the pens tip
	y2 = the ending y position of the pens tip
	so, between these coordinates, a line is drawn
	color = the color of the pen tip - in this case, our display is only black and white
	*/
	display.drawLine(Platform1[0], Platform1[1], Platform1[2], Platform1[3], WHITE); // put our first platform into the buffer
	if (Pipe1[0] > 0) {
		Pipe1[0] = Pipe1[0] - PipeSpeed; // change our pipes x pos
		Pipe1[2] = Pipe1[2] - PipeSpeed; // change our pipes x pos
		display.drawLine(Pipe1[0], Pipe1[1], Pipe1[2], Pipe1[3], WHITE); // draw our first pipe section
	} else {
		ScoreLock = 0; // unlock our score counter
		// now lets change which pipe is used
		if (Pipe1[1] == 63) { // if our pipes x value == 63
			Pipe1[1] = 0; // change the x value to another structure
			Pipe1[3] = 20; // change the x value to another structure
		} else { // if the case is not met, change the x value to a different structure
			Pipe1[1] = 63; // change the x value to another structure
			Pipe1[3] = 40; // change the x value to another structure
		}				
		Pipe1[0] = 138; // set our pipe back to defalt settings
		Pipe1[2] = 138; // set our pipe back to defalt settings
		display.drawLine(Pipe1[0], Pipe1[1], Pipe1[2], Pipe1[3], WHITE); // draw our first pipe section
	}
}

// our characters arrays
int x = 1; // this will hold which index value we will use to draw our character
String character[] = {"*", "*"}; // this array holds our characters images
int CharacterPos[] = {10, 5}; // our characters x and y positions
void Controls() { // this functions checks for input from the controller
	const int Speed = 3; // our characters speed
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
	if (ButtonUp == HIGH && CharacterPos[1] > 5) { // up button detection 
		// This is our jump script
		CharacterPos[1] = CharacterPos[1] - 15; // change the y position
	} 
	if (ButtonLeft == HIGH && CharacterPos[0] > 3) { // left button detection 
		PipeSpeed = PipeSpeed - 1; // Slow our pipes down
		//CharacterPos[0] = CharacterPos[0] - Speed; // change the x position by - speed
	} 
	if (ButtonRight == HIGH && CharacterPos[0] < 120) { // right button detection 
		PipeSpeed = PipeSpeed + 1; // speed our pipes up
		//CharacterPos[0] = CharacterPos[0] + Speed; // change the x position by + speed
	} 
	if (ButtonUp == HIGH && Pause == 1) { // if the up button is pressed and the game is Paused, un-Pause
		Pause = 0; // un-Pause the game
	}
}

void Gravity() { // this function will control the gravitational forces of our character
	if (CharacterPos[1] <= Platform1[1] - 10) { // if either condition is met, fall
		CharacterPos[1] = CharacterPos[1] + 3; // apply gravity
	}
}

void DrawCharacter() { // this function will draw our character to the screen
	if (CharacterPos[0] >= Pipe1[0] && CharacterPos[1] < Pipe1[3] && ScoreLock == 0) { // if the character jumped over a pipe, add 1 to the score
		DrawScore(1); // add one to the score
		//analogWrite(6, 100); // buzz the buzzer
		//delay(100); // delay a few ms
		//analogWrite(6, 0); // turn the buzzer off
		ScoreLock = 1; // lock our score counter
	}
	if (CharacterPos[0] >= Pipe1[0] && CharacterPos[1] > Pipe1[3] && ScoreLock == 0) { // if the character jumped over a pipe, add 1 to the score
		DrawScore(1); // add one to the score
		//analogWrite(6, 100); // buzz the buzzer
		//delay(100); // delay a few ms
		//analogWrite(6, 0); // turn the buzzer off
		ScoreLock = 1; // lock our score counter
	}
	if (x == 0) { // change our index reference
		x = 1; // set our index referenece to one
	} else { // if x == 1
		x = 0; // set our index reference
	}
	OledWrite(CharacterPos[0], CharacterPos[1], 1, character[x]); // draw the character to the buffers
}

void EndGame() { // this function will end our game
	analogWrite(6, 50); // buzz the buzzer
	delay(200); // delay a few ms
	analogWrite(6, 0); // turn the buzzer off
	delay(200); // delay a few ms
	analogWrite(6, 50); // buzz the buzzer
	delay(200); // delay a few ms
	analogWrite(6, 0); // turn the buzzer off
	asm volatile("jmp 0"); // restart the arduino
}

void CheckCollision() { // this function will check for collisions between the character and pipes
	if (Pipe1[1] == 63) { // if the x of Pipe1 is 53, top pipe
		if (CharacterPos[0] >= Pipe1[0] && CharacterPos[1] > Pipe1[3]) { // if a collision is detected with the bottom pipe, end the game
			EndGame(); // end the game
		}
	} else { // if the x of Pipe1 is not 63, bottom pipe
		if (CharacterPos[0] >= Pipe1[0] && CharacterPos[1] < Pipe1[3]) { // if a collision is detected with the top pipe, end the game
			EndGame(); // end the game
		}		
	}
	if (CharacterPos[1] >= 54) { // if the character hits the ground, end game
		EndGame(); // end the game
	}
}

void Debugging() { // this function displays debugging info on the lcd display
	lcd.setCursor(0, 1); // set our lcd cursor position
	lcd.print("X: "); // debugging info
	lcd.print(CharacterPos[0]); // debugging info
	lcd.print(" Y: "); // debugging info
	lcd.print(CharacterPos[1]); // debugging info
	OledWrite(1, 1, 1, "Bird"); // display test string
}
int RomHighScore = EEPROM.read(1); // read our high score from the eeprom address 1
void HighScore() { // this function will control our high score in the eeprom
	if (Score > RomHighScore) { // if the current score is higher than the highest score
		EEPROM.write(1, Score); // write our new high score to eeprom address 1
	}
}

void FlappyAsterisk() { // this will be our 'loop()' function for the game
	HighScore(); // check and store our high rom into a var
	if (Pause == 0) { // only run if the game isn't 'Paused'
		display.clearDisplay(); // clear our oled display (removes ghosting)
		DrawCharacter(); // draw our character to the buffer
		DrawPlatforms(); // put our platforms into the oled buffer
		DrawScore(0); // draw our score to the screen	
		Gravity(); // run our gravity script
		CheckCollision(); // check for collisions with pipes
	} else if (Pause == 1) { // if the game is Paused
		display.clearDisplay(); // clear our oled display (removes old display items)
		OledWrite(20, 20, 2, "_PLAY_"); // display the 'begin' text
		OledWrite(20, 40, 1, "HIGH SCORE"); // display our high score
		OledWrite(40, 50, 2, String(RomHighScore)); // write our high score to the screen
	}
	Controls(); // check for input
	Debugging(); // display our debugging information
	RenderScene(); // render our scene to the oled display
	FlappyAsterisk(); // run our scripts loop
}

void FlappyAsteriskSetup() { // our games 'setup()' function
	delay(400); // delay a few ms
	pinMode(6, OUTPUT); // our buzzer on pin 6
	display.clearDisplay(); // clear oled display from anything left over from last session
	lcd.clear(); // clear our lcd screen from any residue
	LcdWrite(0, 0, "Flappy Asterisk"); // display program name to lcd
	FlappyAsterisk(); // run our games loop
}
