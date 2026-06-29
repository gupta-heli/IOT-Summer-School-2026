/**
 * @file parking_sensor.ino
 * @brief HC-SR04 Ultrasonic Parking Sensor with Multi-Level Alerts.
 *        - Distance > 50cm: Safe, Green LED ON, Buzzer OFF, Serial prints SAFE.
 *        - Distance 20-50cm: Warning, Yellow LED ON, Buzzer beeps every 500ms.
 *        - Distance 10-20cm: Alert, Red LED ON, Buzzer beeps every 200ms.
 *        - Distance < 10cm: Critical, All LEDs flash rapidly, Buzzer continuous.
 *        Uses non-blocking timing (millis()) for buzzer and LED flash cycles.
 *        Course Coursework: Week 3, Assignment Q22
 */

const int TRIG_PIN = 5;
const int ECHO_PIN = 6;

const int LED_GREEN = 8;
const int LED_YELLOW = 9;
const int LED_RED = 10;
const int BUZZER_PIN = 11;

// Timing variables for non-blocking execution
unsigned long lastBuzzerToggle = 0;
bool buzzerActive = false;

unsigned long lastLedToggle = 0;
bool ledFlashState = false;

unsigned long lastSensorRead = 0;
const unsigned long SENSOR_READ_INTERVAL = 100; // Read every 100ms
float currentDistance = 999.0;

unsigned long lastSerialPrint = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.println("Parking Sensor System Initialized.");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Non-blocking trigger and read of the HC-SR04 sensor every 100ms
  if (currentMillis - lastSensorRead >= SENSOR_READ_INTERVAL) {
    lastSensorRead = currentMillis;
    
    // Generate 10-microsecond pulse to Trig
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    // Measure pulse duration on Echo (timeout set to 30000us = ~5 meters maximum)
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    
    if (duration > 0) {
      // Formula: distance = (duration * 0.034) / 2
      currentDistance = (duration * 0.034) / 2.0;
    } else {
      currentDistance = 999.0; // Out of sensor range
    }
  }

  // Multi-level alert state machine
  if (currentDistance > 50.0) {
    // --- STATE: SAFE ---
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    noTone(BUZZER_PIN);
    buzzerActive = false;
    
    if (currentMillis - lastSerialPrint >= 1000) { // Log once a second
      lastSerialPrint = currentMillis;
      Serial.print("Distance: ");
      Serial.print(currentDistance, 1);
      Serial.println(" cm | STATUS: SAFE");
    }
  }
  else if (currentDistance >= 20.0 && currentDistance <= 50.0) {
    // --- STATE: WARNING ---
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, LOW);
    
    // Beep buzzer every 500ms
    if (currentMillis - lastBuzzerToggle >= 500) {
      lastBuzzerToggle = currentMillis;
      buzzerActive = !buzzerActive;
      if (buzzerActive) {
        tone(BUZZER_PIN, 1000); // 1 kHz beep
      } else {
        noTone(BUZZER_PIN);
      }
    }
    
    if (currentMillis - lastSerialPrint >= 1000) {
      lastSerialPrint = currentMillis;
      Serial.print("Distance: ");
      Serial.print(currentDistance, 1);
      Serial.println(" cm | STATUS: WARNING (Beep 500ms)");
    }
  }
  else if (currentDistance >= 10.0 && currentDistance < 20.0) {
    // --- STATE: ALERT ---
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, HIGH);
    
    // Beep buzzer every 200ms
    if (currentMillis - lastBuzzerToggle >= 200) {
      lastBuzzerToggle = currentMillis;
      buzzerActive = !buzzerActive;
      if (buzzerActive) {
        tone(BUZZER_PIN, 1500); // 1.5 kHz beep
      } else {
        noTone(BUZZER_PIN);
      }
    }
    
    if (currentMillis - lastSerialPrint >= 500) { // Log twice a second
      lastSerialPrint = currentMillis;
      Serial.print("Distance: ");
      Serial.print(currentDistance, 1);
      Serial.println(" cm | STATUS: ALERT (Beep 200ms)");
    }
  }
  else {
    // --- STATE: CRITICAL ---
    // Continuous buzzer
    tone(BUZZER_PIN, 2000); // 2 kHz high frequency tone
    
    // Flash all LEDs rapidly (every 100ms)
    if (currentMillis - lastLedToggle >= 100) {
      lastLedToggle = currentMillis;
      ledFlashState = !ledFlashState;
      digitalWrite(LED_GREEN, ledFlashState ? HIGH : LOW);
      digitalWrite(LED_YELLOW, ledFlashState ? HIGH : LOW);
      digitalWrite(LED_RED, ledFlashState ? HIGH : LOW);
    }
    
    if (currentMillis - lastSerialPrint >= 200) { // Log 5 times a second
      lastSerialPrint = currentMillis;
      Serial.print("Distance: ");
      Serial.print(currentDistance, 1);
      Serial.println(" cm | STATUS: CRITICAL ALERT!");
    }
  }
}
