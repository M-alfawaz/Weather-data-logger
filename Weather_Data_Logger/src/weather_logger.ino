#include <Wire.h>
#include <DS3231.h>
#include <SimpleDHT.h>

// DHT11 sensor on pin 2
const int pinDHT11 = 2;
SimpleDHT11 dht11;

// RTC module
DS3231 myRTC(SDA, SCL);

// Track if data has been printed this minute
bool dataPrinted = false;

void setup() {
  Serial.begin(57600);
  Wire.begin();
  myRTC.begin();
  delay(1000); // allow init
}

void loop() {
  // Get current time
  Time now = myRTC.getTime();
  int minute = now.min;
  int second = now.sec;

  // Check if it's time to log data (0,15,30,45 minutes, second 0)
  if ((minute % 15 == 0) && (second == 0)) {
    if (!dataPrinted) {
      // Print timestamp
      Serial.print(now.year); Serial.print("/");
      Serial.print(now.mon); Serial.print("/");
      Serial.print(now.date); Serial.print(" ");
      Serial.print(now.hour); Serial.print(":");
      Serial.print(now.min); Serial.print(":");
      Serial.println(now.sec);

      // Read DHT11
      byte temperature = 0;
      byte humidity = 0;
      byte data[40] = {0};
      if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
        Serial.println("DHT11 read error");
      } else {
        Serial.print("Temp = ");
        Serial.print((int)temperature);
        Serial.print(" C, Humidity = ");
        Serial.print((int)humidity);
        Serial.println(" %");
      }

      dataPrinted = true;
    }
  } else {
    dataPrinted = false;
  }

  delay(1000);
}
