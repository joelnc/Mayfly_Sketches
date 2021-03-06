/**************************************************************************************
Logs temperature and humidity at one second intervals to serial monitor.
Written for Mayfly logger and Grove digital temperature/humidity board (DHT11), with
options for DHT 21 and 22.
Connect the Grove Digital Temp/Humidity board to D10-11 Grove connector on the Mayfly.
After upload open the serial monitor (magnifying lens button) to view data.

modified 7 Jun 2017 by Beth Fisher github.com/fisherba
**************************************************************************************/

#include "Arduino.h"  // Arduino IDE automatically includes Arduino.h, but other IDEs require that you includ
#include "DHT.h"  // Includes the Adafruit DHT-sensor-library 1.3.0+

#define DHTPIN_11 7     // Opposite pin from current DHT22 setup (pin 6).

// Uncomment the digital temperature/humidity model you're using
#define DHTTYPE_11 DHT11    // DHT 11
//#define DHTTYPE DHT22  // DHT 22  (AM2302)
//#define DHTTYPE DHT21  // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht11(DHTPIN_11, DHTTYPE_11);

void setup()
{
    pinMode(22, OUTPUT);      // pin D22 is the enable line for the Mayfly's switched 3.3/5v power lines
    digitalWrite(22, HIGH);   // set this pin high and leave it on for the rest of the sketch
    delay(200);
    Serial.begin(57600);
    Serial.println("Digital Humidity/Temperature");

    dht11.begin();
}

void loop()
{
    // Reading temperature or humidity takes about 250 milliseconds
    // Sensor readings may also be up to 2 seconds old
    float h = dht11.readHumidity();
    float t = dht11.readTemperature(true);

    // check if returns are valid, if they are NaN (not a number) then something went wrong
    if (isnan(t) || isnan(h))
    {
        Serial.println("Failed to read from DHT");
    }
    else
    {
        Serial.print("Humidity: ");
        Serial.print(h);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(t);
        Serial.println(" *F");
				delay(1000);
    }
}
