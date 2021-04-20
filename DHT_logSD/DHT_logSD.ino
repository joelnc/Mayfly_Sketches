// Example testing sketch for various DHT humidity/temperature sensors
// Oringally written by ladyada, public domain

// Modified to write to SD rather than serial print and include RTC timestamps


// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include "Arduino.h" //base
#include "DHT.h"     //dht sensor lib
#include "Wire.h"    //for SD 
#include "SPI.h"
#include "SdFat.h"
#include "Sodaq_DS3231.h" // this is EnviroDIY_DS3231 folder copied and renamed Sodaq...


#define DHTPIN 6     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22  // DHT 22  (AM2302)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Digital pin 12 is the MicroSD slave select pin on the Mayfly
const int8_t SdSsPin = 12;
SdFat SD;

// Init filename for csv
char filename[] = "00000000.CSV";

// Data header  (these lines get written to the beginning of a file when it's created)
const char *dataHeader = "SampleNumber, DT, Temp, Humidity";


int sampleinterval = 3;    //time between samples, in seconds
int samplenum = 1;      // declare the variable "samplenum" and start with 1


// Some pin setup for the DHT
DHT dht(DHTPIN, DHTTYPE);

// Mod fun to just write to file, no check if exists, append data
void setupLogFile() {

	getFileName();
	
  //Initialise the SD card
  if (!SD.begin(SdSsPin))
		{
			Serial.println("Error: SD card failed to initialise or is missing.");
		}
  //Open the file in write mode
  File logFile = SD.open(filename, FILE_WRITE);

  //Add header information if the file did not already exist
  logFile.println(dataHeader);

  //Close the file to save it
  logFile.close();
}


void logData(String rec) {

	getFileName();

	//Re-open the file
  File logFile = SD.open(filename, FILE_WRITE);

  //Write the CSV data
  logFile.println(rec);

  //Close the file to save it
  logFile.close();
}


String createDataRecord() {
	
  //Create a String type data record in csv format
  String data = "";
  data += samplenum;           //creates a string called "data", put in the sample number
  data += ",";                 //adds a comma between values

	// Add datestring
	char tempDt[22];
	DateTime now = rtc.now();
	sprintf(tempDt, "%04d-%02d-%02d %02d:%02d:%02d",  now.year(), now.month(), now.date(), now.hour(), now.minute(), now.second());
	data += tempDt;
	data += ",";	
	
	// Read temperature (true means F rather than c ())
	float t = dht.readTemperature(true);

	// Write temperature
	data += t;
	data += ",";

	// Read humidity
	float h = dht.readHumidity();
	data += h;  	// Write Humidity

	// Wrap up
	samplenum++;   //increment the sample number
	delay(30000);  // <--- This one.. uSec gap between readings
  return data;
}


void setup() {

	Wire.begin();
	rtc.begin();

  //Initialise log file
  setupLogFile();

	//DHT setup
	pinMode(22, OUTPUT);      // pin D22 is the enable line for the Mayfly's switched 3.3/5v power lines
	digitalWrite(22, HIGH);   // set this pin high and leave it on for the rest of the sketch
	delay(2000);

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

} 
