// Made by Dan Jones for a 2015 competition

// some required libraries
#include <IRremote.h> // IR library
#include <LiquidCrystal.h> // lcd display
#include <EEPROM.h> // EEPROM libray
#include <SPI.h> // communications
#include <Wire.h> // i have no idea, but needed
#include <Adafruit_GFX.h> // gfx library for oled
#include <Adafruit_SSD1306.h> // oled display driver
#define OLED_RESET 4 // oled reset code
Adafruit_SSD1306 display(OLED_RESET); // oled reset
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd setup

const int speakerPin = 6;

// variables used for buttons
const int ButtonLeftPin = 7; // left button pin
const int ButtonUpPin = 8; // up button pin
const int ButtonRightPin = 9; // right button pin
int ButtonUp = 0; // up button state
int ButtonLeft = 0; // left button state
int ButtonRight = 0; // right button state

// serial 
String InputString; // this string will hold our serial data

// IR controller values
#define Enter 16236607
#define Up 16187647
#define Down 16220287
#define Off 16203967

// IR variables
int IRpin = 10;
IRrecv irrecv(IRpin);
decode_results results;

// LEDs

int GameState = 0; // if set to 0, our menu script is running, or else a game/function is running

// below are our main functions, thse will allways be the bottow two
// ********************************************************************
void setup() { // our function that is loaded first
        irrecv.enableIRIn(); // start the IR receiver
	ButtonUp = digitalRead(ButtonUpPin); // up button state
	ButtonLeft = digitalRead(ButtonLeftPin); // left button state
	ButtonRight = digitalRead(ButtonRightPin); // right button state
	pinMode(6, OUTPUT); // our buzzer on pin 6
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // lets begin our oled display/connection
	display.clearDisplay(); // clear oled display from anything left over from last session
	lcd.begin(16, 2); // define our lcd properties
	lcd.clear(); // clear our lcd screen from any residue
	LcdWrite(0, 0, "Custom PC Panel"); // display program name to lcd
	LcdWrite(0, 1, "For The Computer"); // display program name to lcd
	MenuDisplay(); // run our main menu script       
        Serial.begin(9600); // begin our serial connection
}

void loop() { // this is the function that will loop through the code
	if (GameState == 0) { // if our menu is selected to run
		Selection(); // this function will control our buttons in the main menu
	}
        while (Serial.available()) { // when we recieve serial data
		char InChar = (char)Serial.read(); // get the incoming data
		if (InChar == '/') { // incoming data
                        analogWrite(6, 50); // buzz the buzzer
	                delay(200); // delay a few ms
                	analogWrite(6, 0); // turn the buzzer off
                        ReceiveData(); // start collecting our data                  
		} 
	}
	RenderScene(); // render our scene to the oled display
}
