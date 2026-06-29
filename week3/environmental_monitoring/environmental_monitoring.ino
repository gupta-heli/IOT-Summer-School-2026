/**
 * @file environmental_monitoring.ino
 * @brief Environmental Monitoring Station using DHT11.
 *        Reads temperature (C & F) and humidity every 2 seconds.
 *        Logs data to Serial in CSV format: timestamp,temp_C,temp_F,humidity.
 *        RED LED (pin 11) ON if Temp > 35°C or Humidity > 80%.
 *        GREEN LED (pin 12) ON if conditions are normal.
 *        Requires Adafruit DHT sensor library.
 *        Course Coursework: Week 3, Assignment Q21
 */

#include <DHT.h>

#define DHTPIN 2       // DHT11 Data Pin
#define DHTTYPE DHT11  // DHT 11 Sensor Type

DHT dht(DHTPIN, DHTTYPE);

const int RED_LED = 11;
const int GREEN_LED = 12;

unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL = 2000; // 2 seconds

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  // Print CSV Header
  Serial.println("timestamp_ms,temp_C,temp_F,humidity");
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentMillis;
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();     // Temperature in Celsius
    float f = dht.readTemperature(true); // Temperature in Fahrenheit
    
    // Validate readings
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("ERROR,NaN,NaN,NaN"); // Log error in CSV pattern
      return;
    }
    
    // Output CSV formatted logs
    Serial.print(currentMillis);
    Serial.print(",");
    Serial.print(t, 1);
    Serial.print(",");
    Serial.print(f, 1);
    Serial.print(",");
    Serial.println(h, 1);
    
    // Check alarm thresholds: Temp > 35C OR Humidity > 80%
    if (t > 35.0 || h > 80.0) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
    } else {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
    }
  }
}
