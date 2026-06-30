/**
 * @file multi_sensor_logger.ino
 * @brief Multi-Sensor Data Logger (DHT11, LDR, HC-SR04).
 *        Reads 3 sensors simultaneously and outputs structured logs to
 *        the Serial Monitor every 5 seconds.
 *        - DHT11: Temperature and Humidity (pin 2)
 *        - LDR: Ambient light mapped to 0-100% (pin A1)
 *        - HC-SR04: Distance in cm (Trig on pin 5, Echo on pin 6)
 *        Course Coursework: Week 3, Assignment Q24
 */

#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int LDR_PIN = A1;
const int TRIG_PIN = 5;
const int ECHO_PIN = 6;

unsigned long lastLogTime = 0;
const unsigned long LOG_INTERVAL = 5000; // 5 seconds

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.println("Multi-Sensor Data Logger Initialized.");
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = currentMillis;
    
    // 1. Read DHT11
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    
    // 2. Read LDR and convert to percentage
    int rawLight = analogRead(LDR_PIN);
    // Assuming LDR is wired so higher voltage = brighter light
    int lightPct = map(rawLight, 0, 1023, 0, 100);
    const char* lightLabel = "Moderate";
    if (lightPct > 70) {
      lightLabel = "Bright";
    } else if (lightPct < 30) {
      lightLabel = "Dark";
    }
    
    // 3. Read HC-SR04
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    float distance = (duration > 0) ? ((duration * 0.034) / 2.0) : -1.0;
    
    // Print in structured format
    Serial.println("=== SENSOR LOG ===");
    
    Serial.print("Time      : ");
    Serial.print(currentMillis);
    Serial.println(" ms");
    
    Serial.print("Temp      : ");
    if (isnan(temp)) {
      Serial.print("Error");
    } else {
      Serial.print(temp, 1);
      Serial.print(" C");
    }
    Serial.print(" | Humidity: ");
    if (isnan(hum)) {
      Serial.print("Error");
    } else {
      Serial.print((int)hum);
      Serial.print("%");
    }
    Serial.println();
    
    Serial.print("Light     : ");
    Serial.print(lightPct);
    Serial.print("% (");
    Serial.print(lightLabel);
    Serial.println(")");
    
    Serial.print("Distance  : ");
    if (distance < 0) {
      Serial.println("Out of Range");
    } else {
      Serial.print((int)distance);
      Serial.println(" cm");
    }
    
    Serial.println("==================");
  }
}
