/**
 * @file night_light.ino
 * @brief PWM Fading Night Light with 3 Switchable Modes.
 *        Modes:
 *        0: Slow breathing (3-second cycle)
 *        1: Fast pulse (0.5-second cycle)
 *        2: SOS Morse code pattern (... --- ...)
 *        Toggled via button on pin 2 (external pull-down).
 *        LED is driven on PWM pin 9.
 *        Fully non-blocking implementation ensures instant button response.
 *        Course Coursework: Week 2, Assignment Q17
 */

const int LED_PIN = 9;      // PWM Pin for LED
const int BTN_PIN = 2;      // Button Pin

enum LightMode {
  MODE_SLOW_BREATH,
  MODE_FAST_PULSE,
  MODE_SOS
};

LightMode currentMode = MODE_SLOW_BREATH;

// Button State variables
bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 50;

// Timing variables for breathing modes
unsigned long cycleStartTime = 0;

// SOS Morse code definitions:
// Dot: 200ms ON, 200ms OFF
// Dash: 600ms ON, 200ms OFF
// Letter space: 600ms OFF (400ms added to last 200ms OFF)
// Word space: 2000ms OFF
const int SOS_STEPS = 18;
const int sosDurations[SOS_STEPS] = {
  200, 200,  // Dot 1 (ON, OFF)
  200, 200,  // Dot 2 (ON, OFF)
  200, 600,  // Dot 3 (ON, OFF with letter space)
  600, 200,  // Dash 1 (ON, OFF)
  600, 200,  // Dash 2 (ON, OFF)
  600, 600,  // Dash 3 (ON, OFF with letter space)
  200, 200,  // Dot 1 (ON, OFF)
  200, 200,  // Dot 2 (ON, OFF)
  200, 2000  // Dot 3 (ON, OFF with word space/cycle end)
};
int sosIndex = 0;
unsigned long sosStartTime = 0;

void printModeName(LightMode mode) {
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms] MODE SWITCHED TO: ");
  switch (mode) {
    case MODE_SLOW_BREATH:
      Serial.println("Slow Breathing (3s cycle)");
      break;
    case MODE_FAST_PULSE:
      Serial.println("Fast Pulse (0.5s cycle)");
      break;
    case MODE_SOS:
      Serial.println("SOS Morse Code (... --- ...)");
      break;
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT); // External pull-down resistor
  Serial.begin(9600);
  
  cycleStartTime = millis();
  printModeName(currentMode);
}

void loop() {
  unsigned long currentMillis = millis();

  // Read button with debounce
  bool buttonReading = digitalRead(BTN_PIN);
  if (buttonReading != lastButtonState) {
    lastDebounceTime = currentMillis;
  }

  if ((currentMillis - lastDebounceTime) > DEBOUNCE_DELAY) {
    // Check for rising edge (press)
    if (buttonReading == HIGH && lastButtonState == LOW) {
      // Switch mode
      if (currentMode == MODE_SLOW_BREATH) {
        currentMode = MODE_FAST_PULSE;
      } else if (currentMode == MODE_FAST_PULSE) {
        currentMode = MODE_SOS;
        sosIndex = 0;
        sosStartTime = currentMillis;
      } else {
        currentMode = MODE_SLOW_BREATH;
      }
      cycleStartTime = currentMillis; // reset cycle timer
      printModeName(currentMode);
      delay(150); // Additional delay to prevent bounce double-registers
    }
  }
  lastButtonState = buttonReading;

  // Execute current mode behavior
  if (currentMode == MODE_SLOW_BREATH) {
    // 3-second cycle = 3000ms
    unsigned long elapsed = (currentMillis - cycleStartTime) % 3000;
    // Generate triangle wave 0 -> 255 -> 0
    int brightness = 255 * (1.0 - abs(2.0 * (float)elapsed / 3000.0 - 1.0));
    analogWrite(LED_PIN, brightness);
  } 
  else if (currentMode == MODE_FAST_PULSE) {
    // 0.5-second cycle = 500ms
    unsigned long elapsed = (currentMillis - cycleStartTime) % 500;
    // Generate triangle wave 0 -> 255 -> 0
    int brightness = 255 * (1.0 - abs(2.0 * (float)elapsed / 500.0 - 1.0));
    analogWrite(LED_PIN, brightness);
  } 
  else if (currentMode == MODE_SOS) {
    // Non-blocking step-by-step SOS execution
    if (currentMillis - sosStartTime >= (unsigned long)sosDurations[sosIndex]) {
      sosIndex = (sosIndex + 1) % SOS_STEPS;
      sosStartTime = currentMillis;
    }
    
    // Even steps are ON (HIGH brightness), odd steps are OFF
    if (sosIndex % 2 == 0) {
      analogWrite(LED_PIN, 255); // Full brightness during active pulses
    } else {
      analogWrite(LED_PIN, 0);   // Dark during spaces
    }
  }
}
