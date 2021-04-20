#include <OneWire.h>
#include <DallasTemperature.h>
#include <PCD8544.h>             // Nokia 5110
#include "Wire.h"               
#include <SD.h>
#include <SPI.h>                 // SD
#include "RTClib.h"              //Date As Filename
#include <string.h>              //Date As Filename


#define DS1307_ADDRESS 0x68

RTC_DS1307 RTC;
char filename[] = "00000000.CSV";
File myFile;

void setup() {
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect))
		{
			lcd.println("Card failed");
			// don't do anything more:
			return;
		}
  lcd.println("CARD OK");
  delay(2000);
 
	getFileName();
	lcd.setCursor(0,3);
	lcd.println(filename);
}


void getFileName() {
	DateTime now = RTC.now();
  // Turns file_today_name into date.txt format
  sprintf(filename, "%02d%02d%02d.csv", now.year(), now.month(), now.day());
}


void loop() {

	GetClock();
  if (hour == 0 && minute == 0 && second <2)
		{
			getFileName();
		}
 
  k=k+1; 

  if (k>9 )
		{ 
			myFile = SD.open(filename, FILE_WRITE);//<<<<<<<<<<<<< OPEN
			myFile.print(hour);
			myFile.print(":");
			myFile.print(minute);
			myFile.print(":");
			myFile.print(second);
			myFile.print(",");

			myFile.print(InTemp);
			myFile.print(",");
			myFile.print(OutTemp);
			myFile.print(",");
			myFile.print(DrainTemp);
			myFile.print(",");
			myFile.print(diff);
			myFile.println();
			myFile.close();//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CLOSE
       
      k=0;
		}
}  // loop ends here


//sensorValue function
float sensorValue (byte deviceAddress[])
{, 5);

  tempC = sensors.getTempC (deviceAddress);
  return tempC;
}


byte bcdToDec(byte val) {
  // Convert binary coded decimal to normal decimal bers
  return ( (val/16*10) + (val%16) );
}


void GetClock(){
  // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);
  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);

  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read() & 0b111111); //24 hour time
  weekDay = bcdToDec(Wire.read()); //0-6 -> sunday - Saturday
  monthDay = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}




