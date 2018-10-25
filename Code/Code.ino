#include "DHT.h"
#include "ThingSpeak.h"

#include <SPI.h>
#include <ESP8266WiFi.h>
char ssid[] = "YOUR_WIFI_SSID";    //  your network SSID (name) 
char pass[] = "YOUR_WIFI_PASSWORD";   // your network password
int status = WL_IDLE_STATUS;
WiFiClient  client;


unsigned long myChannelNumber = "YOUR CHANNEL NO.";
const char * myWriteAPIKey = "YOUR WRITE API KEY";

DHT dht;

void setup()
{
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  dht.setup(D0);   /* D1 is used for data communication */
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());/* Delay of amount equal to sampling period */
  float humidity = dht.getHumidity();/* Get humidity value */
  float temperature = dht.getTemperature();/* Get temperature value */
  Serial.print(dht.getStatusString());/* Print status of communication */
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.println(dht.toFahrenheit(temperature), 1);/* Convert temperature to Fahrenheit units */
  ThingSpeak.setField(1,humidity);
  ThingSpeak.setField(2,temperature);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  delay(2000);
}
