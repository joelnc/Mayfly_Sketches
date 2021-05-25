#include "Adafruit_seesaw.h"
#include "LiquidCrystal.h"

// Note, initial cap readings were 30ish.  Via mayfly forums found tip to change par in
// seesaw.cpp file from 1000 to 4000.  Did so locally, seems to have worked.  Put link here.
Adafruit_seesaw ss;

// Mayfly pin numbering for LCD
const int rs = 20, en = 21, d4 = 10, d5 = 11, d6 = 8, d7 = 9; // D20/7, D21/14, etc
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup() {
	// Mayfly stuff
	pinMode(22, OUTPUT);      // pin D22 is the enable line for the Mayfly's switched 3.3/5v power lines
	digitalWrite(22, HIGH);   // set this pin high and leave it on for the rest of the sketch

	// set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

	// Serial stuff
	Serial.begin(115200);
  Serial.println("seesaw Soil Sensor example!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }

	// Print a message to the LCD.
  //lcd.print("hello, world!");

}

void loop() {
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);
  delay(4000);

  // Turn off the display:
	lcd.print(capread);
  delay(2000);
	lcd.clear();
  // Turn on the display:
  /* lcd.display(); */
  /* delay(5000); */

}
