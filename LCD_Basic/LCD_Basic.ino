/*
  LiquidCrystal Library - display() and noDisplay()

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD and uses the
 display() and noDisplay() functions to turn on and off
 the display.

The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008 by David A. Mellis
 library modified 5 Jul 2009 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009 by Tom Igoe
 modified 22 Nov 2010 by Tom Igoe
 modified 7 Nov 2016 by Arturo Guadalupi
 This example code is in the public domain.
 http://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay



// Two knob wring diagram
/* https://www.circuitbasics.com/raspberry-pi-lcd-set-up-and-programming-in-python/ */

// Uno pin setup
/* https://www.arduino.cc/en/Tutorial/LibraryExamples/HelloWorld */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//Uno pin numbering
/* const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; */

// Mayfly pin numbering
const int rs = 20, en = 21, d4 = 10, d5 = 11, d6 = 8, d7 = 9; // D20/7, D21/14, etc

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

	// Mayfly stuff
	pinMode(22, OUTPUT);      // pin D22 is the enable line for the Mayfly's switched 3.3/5v power lines
	digitalWrite(22, HIGH);   // set this pin high and leave it on for the rest of the sketch

	// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // Turn off the display:
  lcd.noDisplay();
  delay(1500);
  // Turn on the display:
  lcd.display();
  delay(5000);
}
