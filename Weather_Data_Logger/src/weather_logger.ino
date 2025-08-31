#include <Wire.h>
#include <DS3231.h>
#include <SimpleDHT.h>

// ----- Sensors -----
const int PIN_DHT11 = 2;
SimpleDHT11 dht11;

// ----- RTC (DS3231) -----
DS3231 myRTC(SDA, SCL);   // uses I2C pins

// Track if we already printed in this exact minute/second slot
bool dataPrinted = false;

void setup() {
  Serial.begin(57600);     // per report
  Wire.begin();
  myRTC.begin();
  delay(1000);             // allow init
}

void loop() {
  // Current time
  Time now = myRTC.getTime();
  int minute = now.min;
  int second = now.sec;

  // Log at 0,15,30,45 minute marks when seconds == 0
  if ((minute % 15 == 0) && (second == 0)) {
    if (!dataPrinted) {
      // Timestamp
      Serial.print(now.year); Serial.print("/");
      Serial.print(now.mon);  Serial.print("/");
      Serial.print(now.date); Serial.print(" ");
      Serial.print(now.hour); Serial.print(":");
      Serial.print(now.min);  Serial.print(":");
      Serial.println(now.sec);

      // Read DHT11
      byte temperature = 0, humidity = 0;
      byte data[40] = {0};
      if (dht11.read(PIN_DHT11, &temperature, &humidity, data)) {
        Serial.println("DHT11 read error");
      } else {
        Serial.print("Temp = ");
        Serial.print((int)temperature);
        Serial.print(" C, Humidity = ");
        Serial.print((int)humidity);
        Serial.println(" %");
      }

      dataPrinted = true; // prevent re-printing within the same second
    }
  } else {
    dataPrinted = false;
  }

  delay(1000);
}
