/**
 * @file street_light.ino
 * @brief Smart Street Light Controller (LDR + PIR).
 *        - Daylight (LDR > Threshold): LED is completely OFF.
 *        - Night (LDR <= Threshold): Enables motion detection mode.
 *          - PIR detects motion: LED at full brightness (100% PWM) for 30 seconds.
 *          - No motion after 30 seconds: LED dims to 20% PWM (energy saving).
 *        Logs events to Serial Monitor in [HH:MM:SS] format using millis().
 *        Course Coursework: Week 3, Assignment Q23
 */

// Pin Mappings
const int LDR_PIN = A1;     // Analog LDR input
const int PIR_PIN = 2;      // Digital PIR input
const int LED_PIN = 9;      // PWM LED output

// Thresholds and configuration
const int LDR_DARK_THRESHOLD = 400; // Adjust based on calibration (LDR < 400 = Dark)
const unsigned long LIGHT_ON_DURATION = 30000; // 30 seconds (30000ms)

enum LightState {
  STATE_DAY,
  STATE_NIGHT_HIGH,
  STATE_NIGHT_DIM
};

LightState currentState = STATE_DAY;
unsigned long motionTimerStart = 0;

void printTimestampedEvent(const char* desc) {
  unsigned long totalSecs = millis() / 1000;
  int s = totalSecs % 60;
  int m = (totalSecs / 60) % 60;
  int h = (totalSecs / 3600) % 24;
  
  char timeStr[12];
  sprintf(timeStr, "[%02d:%02d:%02d]", h, m, s);
  Serial.print(timeStr);
  Serial.print(" EVENT: ");
  Serial.println(desc);
}

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  
  Serial.println("Smart Street Light Controller Booting Up...");
  // Initial check
  int ldrValue = analogRead(LDR_PIN);
  if (ldrValue < LDR_DARK_THRESHOLD) {
    currentState = STATE_NIGHT_DIM;
    analogWrite(LED_PIN, 51); // 20% of 255 = 51
    printTimestampedEvent("System started in NIGHT mode (Dim, 20% brightness).");
  } else {
    currentState = STATE_DAY;
    analogWrite(LED_PIN, 0);  // OFF
    printTimestampedEvent("System started in DAY mode (Light OFF).");
  }
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Read sensors
  int ldrValue = analogRead(LDR_PIN);
  bool motionDetected = (digitalRead(PIR_PIN) == HIGH);
  
  // Main State Machine
  switch (currentState) {
    case STATE_DAY:
      // If it gets dark
      if (ldrValue < LDR_DARK_THRESHOLD) {
        if (motionDetected) {
          currentState = STATE_NIGHT_HIGH;
          motionTimerStart = currentMillis;
          analogWrite(LED_PIN, 255); // 100% Brightness
          printTimestampedEvent("Night detected + Motion. Light set to 100% brightness.");
        } else {
          currentState = STATE_NIGHT_DIM;
          analogWrite(LED_PIN, 51);  // 20% Brightness
          printTimestampedEvent("Night detected. No motion. Light set to 20% brightness.");
        }
      }
      break;

    case STATE_NIGHT_HIGH:
      // If daylight returns
      if (ldrValue >= LDR_DARK_THRESHOLD) {
        currentState = STATE_DAY;
        analogWrite(LED_PIN, 0); // OFF
        printTimestampedEvent("Daylight detected. Light turned OFF.");
      }
      // If motion is re-triggered, reset the 30-second timer
      else if (motionDetected) {
        motionTimerStart = currentMillis;
      }
      // If timer expires after 30 seconds of no motion
      else if (currentMillis - motionTimerStart >= LIGHT_ON_DURATION) {
        currentState = STATE_NIGHT_DIM;
        analogWrite(LED_PIN, 51); // Dim to 20%
        printTimestampedEvent("Timeout: No motion for 30s. Light dimmed to 20% brightness.");
      }
      break;

    case STATE_NIGHT_DIM:
      // If daylight returns
      if (ldrValue >= LDR_DARK_THRESHOLD) {
        currentState = STATE_DAY;
        analogWrite(LED_PIN, 0); // OFF
        printTimestampedEvent("Daylight detected. Light turned OFF.");
      }
      // If motion is detected while in dim state
      else if (motionDetected) {
        currentState = STATE_NIGHT_HIGH;
        motionTimerStart = currentMillis;
        analogWrite(LED_PIN, 255); // 100% Brightness
        printTimestampedEvent("Motion detected. Light set to 100% brightness.");
      }
      break;
  }
  
  delay(100); // Polling stability
}
