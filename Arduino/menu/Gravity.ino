// this tab will contain our gravity tests

/*
the idea in this 'program' is to basically play around with gravity values, and possibly create a cannon like device that will shoot balls
and have x and y gravity values affecting its flight arc
*/
// here we define some key variables
String BallChar[] = {"%"}; // this array holds our balls font
int Size = 2; // this is our balls size - valid sizes 1-2
int BallPos[] = {1, 10}; // this array holds our balls x and y position - x = 0 y = 1
int BallSpeed[] = {1, 4}; // this array holds our balls x and y speed - x = 0 y = 1

void BallCheckPos() { // this function will check the balls position and deal with it accordingly, also it controls the button actions
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
	if (ButtonUp == HIGH) { // middle button detection 
		BallPos[1] = BallPos[1] - 5; // raise BallyPos
	} 
	if (ButtonLeft == HIGH) { // left button detection 
		BallPos[0] = BallPos[0] - 4; // change our BallxPos
	} 
	if (ButtonRight == HIGH) { // right button detection 
		BallPos[0] = BallPos[0] + 4; // change our BallxPos
	} 
}

void BallGravity() { // this function will control our balls gravity and move it accordingly
	if (BallPos[1] < 70) { // if the ball is not at the bottom of the screen
		BallPos[1] += BallSpeed[1]; // add our BallySpeed to the current BallyPos
	} else { // if we are touching the outer bounds
		BallPos[1] = -60; // change our BallyPos to - 60 (this makes the animation smooth)
	}
}

void DrawBall() { // this function will draw our ball to the oled buffer
	OledWrite(BallPos[0], BallPos[1], Size, BallChar[0]); // this places our ball into the oled buffer
}

void DebugInfo() { // this function will display debugging info to our lcd display
	LcdWrite(0, 2, "X:"); // debug info
	LcdWrite(3, 2, String(BallPos[0])); // debug info
	LcdWrite(9, 2, "Y:"); // debug info
	LcdWrite(11, 2, String(BallPos[1])); // debug info
}

void GravityGame() { // this is our main loop for this 'test'
	BallCheckPos(); // check our balls position/check for controls
	BallGravity(); // apply our gravity
	DrawBall(); // place our ball into the oleds buffer
	RenderScene(); // render our scene
	display.clearDisplay(); // clear our oled display (removes old display items)
	DebugInfo(); // display some debug information to the lcd display
	GravityGame(); // loop
}

void GravitySetup() { // this function is our 'setup' script for this 'test'
	display.clearDisplay(); // clear our oled display (removes old display items)
	GravityGame(); // run our gravity 'test' loop
}
