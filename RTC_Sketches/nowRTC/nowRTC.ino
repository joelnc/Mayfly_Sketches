// Date and time functions using RX8025 RTC connected via I2C and Wire lib
// Copy of enviro lib 'now' sketch to test if clock time from adjust sketch works
// So after setting clock via adjustRTC, turn off, disconnect wait a few minutes
// .. then run this to confirm it retained time via button battery 
#include <Wire.h>
#include "Sodaq_DS3231.h"

char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

void setup () 
{
    Serial.begin(57600);
    Wire.begin();
    rtc.begin();
}

uint32_t old_ts;

void loop () 
{
	DateTime now = rtc.now(); //get the current date-time
	uint32_t ts = now.getEpoch();
	
	if (old_ts == 0 || old_ts != ts) {
		old_ts = ts;
		Serial.print(now.year(), DEC);
		Serial.print('/');
		Serial.print(now.month(), DEC);
		Serial.print('/');
		Serial.print(now.date(), DEC);
		Serial.print(' ');
		Serial.print(now.hour(), DEC);
		Serial.print(':');
		Serial.print(now.minute(), DEC);
		Serial.print(':');
		Serial.print(now.second(), DEC);
		Serial.print(' ');
		Serial.print(weekDay[now.dayOfWeek()]);
		Serial.println();
		Serial.println();
	}
	delay(1000);
}
