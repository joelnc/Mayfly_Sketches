/**************************************************************************************
Logs temperature and humidity at 5 sec intervals to serial monitor.
Adapted here to run the 

modified 7 Jun 2017 by Beth Fisher github.com/fisherba
further modified 21 Apr 2021 by github.com/joelnc
**************************************************************************************/

#include "Arduino.h"  // Arduino IDE automatically includes Arduino.h, but other IDEs require that you includ
#include "DHT.h"  // Includes the Adafruit DHT-sensor-library 1.3.0+

#define DHTPIN_11 7     // Opposite pin from current DHT22 setup (pin 6).
#define DHTPIN_22 6     // Pin 6 for the 22.

// Uncomment the digital temperature/humidity model you're using
#define DHTTYPE_11 DHT11    // DHT 11
#define DHTTYPE_22 DHT22    // DHT 22

//#define DHTTYPE DHT22  // DHT 22  (AM2302)
//#define DHTTYPE DHT21  // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Either pull power and ground off analog side for sensor two, or digitals to a bus

// Setup stuff for the two
DHT dht_11(DHTPIN_11, DHTTYPE_11);
DHT dht_22(DHTPIN_22, DHTTYPE_22);

void setup()
{
    pinMode(22, OUTPUT);      // pin D22 is the enable line for the Mayfly's switched 3.3/5v power lines
    digitalWrite(22, HIGH);   // set this pin high and leave it on for the rest of the sketch
    delay(200);
    Serial.begin(57600);
    Serial.println("Digital Humidity/Temperature");

    dht_11.begin();
    dht_22.begin();
}

void loop()
{
    // Reading temperature or humidity takes about 250 milliseconds
    // Sensor readings may also be up to 2 seconds old
    float h_11 = dht_11.readHumidity();
    float t_11 = dht_11.readTemperature(true);

    float h_22 = dht_22.readHumidity();
    float t_22 = dht_22.readTemperature(true);

    // check if returns are valid, if they are NaN (not a number) then something went wrong
    if (isnan(t_11) || isnan(h_11))
    {
        Serial.println("Failed to read from DHT");
    }
    else
    {
        Serial.print("Humidity11: ");
        Serial.print(h_11);
        Serial.print(" %\t");
        Serial.print("Temp11: ");
        Serial.print(t_11);
        Serial.println(" *F");
        Serial.print("Humidity22: ");
        Serial.print(h_22);
        Serial.print(" %\t");
        Serial.print("Temp22: ");
        Serial.print(t_22);
        Serial.println(" *F");
				delay(5000);
    }
}
