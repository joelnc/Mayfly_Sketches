// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include "Arduino.h" //base
#include "DHT.h"     //dht sensor lib
#include "Wire.h"    //for SD 
#include "SPI.h"
#include "SdFat.h"
#include "Sodaq_DS3231.h" // this is EnviroDIY_DS3231 folder copied and renamed Sodaq...

char filename[] = "00000000.CSV";
/* File logFile; */

//year, month, date, hour, min, sec and week-day(starts from 0 and goes to 6)
//writing any non-existent time-data may interfere with normal operation of the RTC.
//Take care of week-day also.
//DateTime dt(2021, 04, 10, 22, 20, 50, 5);

// My attempt to go around 'set date' above and use already set rtc
// DateTime now =rtc.now(); // get current date time



#define DHTPIN 6     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22  // DHT 22  (AM2302)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

//Digital pin 12 is the MicroSD slave select pin on the Mayfly
const int8_t SdSsPin = 12;
SdFat SD;


//Data header  (these lines get written to the beginning of a file when it's created)
/* const char *loggerName = "Mayfly microSD Card Tester"; */
const char *dataHeader = "SampleNumber, DT, Temp, Humidity";


int sampleinterval = 3;    //time between samples, in seconds
int samplenum = 1;      // declare the variable "samplenum" and start with 1


DHT dht(DHTPIN, DHTTYPE);

void setupLogFile() { // modded to just overwrite?

	getFileName();
	
  //Initialise the SD card
  if (!SD.begin(SdSsPin))
		{
			Serial.println("Error: SD card failed to initialise or is missing.");
		}

  //Check if the file already exists
  //bool oldFile = SD.exists(fileName);

  //Open the file in write mode
  File logFile = SD.open(filename, FILE_WRITE);
  /* File logFile = SD.open(fileName, FILE_WRITE); */

  //Add header information if the file did not already exist
  /* if (!oldFile) */
	/* 	{ */
  /* logFile.println(loggerName); */
  logFile.println(dataHeader);
	/* } */

  //Close the file to save it
  logFile.close();
}


void logData(String rec) {

	getFileName();
  //Re-open the file
  File logFile = SD.open(filename, FILE_WRITE);
  /* File logFile = SD.open(fileName, FILE_WRITE); */

  //Write the CSV data
  logFile.println(rec);

  //Close the file to save it
  logFile.close();
}


String createDataRecord() {
	
  //Create a String type data record in csv format
  //SampleNumber, Battery
  String data = "";
  data += samplenum;           //creates a string called "data", put in the sample number
  data += ",";                 //adds a comma between values

	// Add datestring
	char buf1[22];
	DateTime now = rtc.now();
	sprintf(buf1, "%04d-%02d-%02d %02d:%02d:%02d",  now.year(), now.month(), now.date(), now.hour(), now.minute(), now.second());
	data += buf1;
	data += ",";	
	
	// Read temperature (true means F rather than c ())
	float t = dht.readTemperature(true);
	// Write temperagru
	data += t;
	data += ",";

	// Read humidity
	float h = dht.readHumidity();
	// Write Humidity
	data += h;

	// Wrap up
	samplenum++;   //increment the sample number
	delay(1000);
  return data;
}


void setup() {

	Wire.begin();
	rtc.begin();
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif
	
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

	// set initial time from top of file
	//rtc.setDateTime(dt);

  //Initialise log file
  setupLogFile();

  //Echo the data header to the serial connection
  Serial.println(dataHeader);
	//DHT setup
	pinMode(22, OUTPUT);      // pin D22 is the enable line for the Mayfly's switched 3.3/5v power lines
	digitalWrite(22, HIGH);   // set this pin high and leave it on for the rest of the sketch
	delay(2000);
	Serial.begin(57600);
	Serial.println("Digital Humidity/Temperature");

	dht.begin();
}

void getFileName() {
	DateTime now = rtc.now();
  // Turns file_today_name into date.txt format
  sprintf(filename, "%02d%02d%02d.csv", now.year(), now.month(), now.date());
}

void loop() {

	DateTime now = rtc.now();

  String dataRec = createDataRecord();

  //Save the data record to the log file
  logData(dataRec);

	// Reading temperature or humidity takes about 250 milliseconds
	// Sensor readings may also be up to 2 seconds old
/* 	delay(200); */
/* 	float h = dht.readHumidity(); */
/* 	float t = dht.readTemperature(true); */

/* 	// check if returns are valid, if they are NaN (not a number) then something went wrong */
/* 	if (isnan(t) || isnan(h)) */
/*     { */
/* 			Serial.println("Failed to read from DHT"); */
/*     } */
/* 	else */
/*     { */
/* 			Serial.print("Stamp: "); */
/* 			Serial.print(now.year(), DEC); */
/* 			Serial.print('-'); */
/* 			Serial.print(now.month(), DEC); */
/* 			Serial.print('-'); */
/* 			Serial.print(now.date(), DEC); */
/* 			Serial.print(" "); */
/* 			Serial.print(now.hour(), DEC); */
/* 			Serial.print(':'); */
/* 			Serial.print(now.minute(), DEC); */
/* 			Serial.print(':'); */
/* 			Serial.print(now.second(), DEC); /// just printing 1s? */
/* 			Serial.print(" %\t"); */
/* 			Serial.print("HumidityYC: "); */
/* 			Serial.print(h); */
/* 			Serial.print(" %\t"); */
/* 			Serial.print("TemperatureYA: "); */
/* 			Serial.print(t); */
/* 			Serial.println(" *F"); */
/*     } */

} 
