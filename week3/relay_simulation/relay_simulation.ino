/**
 * @file relay_simulation.ino
 * @brief Relay-Controlled AC Device Simulation (with Hysteresis & Manual Override).
 *        - Simulated AC device (LED representing Relay) on pin 8.
 *        - Temperature read from DHT11 on pin 2.
 *        - Automatic Hysteresis Mode:
 *          - Temp > 32.0°C -> Relay turns ON (AC ON)
 *          - Temp < 28.0°C -> Relay turns OFF (AC OFF)
 *          - 28.0°C <= Temp <= 32.0°C -> Keep previous state
 *        - Manual Override Button on pin 3:
 *          - Short press (< 1s) toggles relay state directly and locks into MANUAL mode.
 *          - Long press (>= 2s) restores AUTO mode.
 *        Logs all state changes and temperature readings to the Serial Monitor.
 *        Course Coursework: Week 3, Assignment Q27
 */

#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int RELAY_PIN = 8;     // Relay simulator (LED) pin
const int BTN_PIN = 3;       // Manual Override button pin

// Hysteresis Thresholds
const float TEMP_HIGH = 32.0; // Turn on temperature
const float TEMP_LOW = 28.0;  // Turn off temperature

// System States
bool relayState = false;
bool manualOverride = false;
float currentTemp = 0.0;

// Button timing for short/long press
unsigned long buttonPressStart = 0;
bool buttonWasPressed = false;
const unsigned long LONG_PRESS_TIME = 2000; // 2 seconds

unsigned long lastSensorRead = 0;
const unsigned long SENSOR_INTERVAL = 2000; // Read DHT11 every 2 seconds

void updateRelay(bool newState, const char* reason) {
  if (relayState != newState) {
    relayState = newState;
    digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
    
    Serial.print("[RELAY CHANGE] State: ");
    Serial.print(relayState ? "ON (AC Active)" : "OFF (AC Idle)");
    Serial.print(" | Temp: ");
    Serial.print(currentTemp, 1);
    Serial.print(" C | Mode: ");
    Serial.print(manualOverride ? "MANUAL OVERRIDE" : "AUTO");
    Serial.print(" | Reason: ");
    Serial.println(reason);
  }
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT); // External pull-down
  digitalWrite(RELAY_PIN, LOW);
  
  Serial.begin(9600);
  dht.begin();
  
  Serial.println("Relay Hysteresis Simulator Initialized.");
  Serial.println("Hysteresis thresholds: ON > 32°C, OFF < 28°C");
  Serial.println("Button: Short-press to toggle relay (MANUAL), Long-press (2s) to restore AUTO.");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // 1. Read Button State and detect short/long press
  bool btnState = (digitalRead(BTN_PIN) == HIGH);
  
  if (btnState && !buttonWasPressed) {
    // Button just pressed
    buttonPressStart = currentMillis;
    buttonWasPressed = true;
  } 
  else if (!btnState && buttonWasPressed) {
    // Button just released
    unsigned long pressDuration = currentMillis - buttonPressStart;
    buttonWasPressed = false;
    
    if (pressDuration >= LONG_PRESS_TIME) {
      // Long press -> Restore AUTO Mode
      if (manualOverride) {
        manualOverride = false;
        Serial.println("EVENT: Long-press detected. Restoring AUTO control.");
        // Force evaluation of temperature next loop
        lastSensorRead = 0; 
      }
    } else {
      // Short press -> Toggle Relay state and force MANUAL Mode
      manualOverride = true;
      bool targetState = !relayState;
      updateRelay(targetState, "Manual override button press");
    }
  }

  // 2. Read temperature and apply logic every 2 seconds
  if (currentMillis - lastSensorRead >= SENSOR_INTERVAL) {
    lastSensorRead = currentMillis;
    
    float t = dht.readTemperature();
    if (!isnan(t)) {
      currentTemp = t;
      
      // If in AUTO mode, apply hysteresis logic
      if (!manualOverride) {
        if (currentTemp > TEMP_HIGH) {
          updateRelay(true, "Temperature exceeded 32°C");
        } 
        else if (currentTemp < TEMP_LOW) {
          updateRelay(false, "Temperature fell below 28°C");
        }
      }
      
      // Periodically print current status to Serial Monitor
      Serial.print("LOG: Temp: ");
      Serial.print(currentTemp, 1);
      Serial.print(" C | Relay: ");
      Serial.print(relayState ? "ON" : "OFF");
      Serial.print(" | Mode: ");
      Serial.println(manualOverride ? "MANUAL" : "AUTO");
    } else {
      Serial.println("LOG ERROR: Failed to read from DHT11!");
    }
  }
}
