/**
 * @file dc_motor_control.ino
 * @brief DC Motor Speed & Direction Control via L298N Driver.
 *        - Potentiometer on A0 sets speed (0-255 PWM).
 *        - Button on pin 2 toggles Direction (Forward/Reverse).
 *        - Button on pin 3 toggles State (Start/Stop).
 *        - L298N pins: ENA (pin 9, PWM), IN1 (pin 7), IN2 (pin 8).
 *        - Displays Direction, Speed (0-100%), and State on Serial Monitor.
 *        Course Coursework: Week 3, Assignment Q26
 */

// L298N Driver Pin Mappings
const int ENA_PIN = 9;   // PWM Speed control pin
const int IN1_PIN = 7;   // Direction Control 1
const int IN2_PIN = 8;   // Direction Control 2

// Input Pin Mappings
const int POT_PIN = A0;      // Potentiometer Analog input
const int BTN_DIR = 2;       // Direction Toggle button
const int BTN_STATE = 3;     // Start/Stop Toggle button

// Motor Control Variables
bool motorRunning = false;
bool isForward = true;
int rawSpeed = 0;
int lastSpeedPct = -1;
bool lastRunningState = false;
bool lastDirectionState = true;

// Debouncing variables
bool lastDirBtnState = LOW;
bool lastStateBtnState = LOW;
unsigned long lastDebounceDir = 0;
unsigned long lastDebounceState = 0;
const unsigned long DEBOUNCE_DELAY = 50;

unsigned long lastSerialPrint = 0;

void setup() {
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  
  pinMode(BTN_DIR, INPUT);   // External pull-down
  pinMode(BTN_STATE, INPUT); // External pull-down
  
  Serial.begin(9600);
  Serial.println("L298N DC Motor Control System Initialized.");
  updateMotorOutputs();
}

void loop() {
  unsigned long currentMillis = millis();

  // Read raw inputs
  int potValue = analogRead(POT_PIN);
  rawSpeed = map(potValue, 0, 1023, 0, 255); // Convert to 8-bit PWM
  int speedPct = map(rawSpeed, 0, 255, 0, 100);

  bool dirBtnReading = digitalRead(BTN_DIR);
  bool stateBtnReading = digitalRead(BTN_STATE);

  // Debounce Direction Button
  if (dirBtnReading != lastDirBtnState) {
    lastDebounceDir = currentMillis;
  }
  if ((currentMillis - lastDebounceDir) > DEBOUNCE_DELAY) {
    if (dirBtnReading == HIGH && lastDirBtnState == LOW) {
      isForward = !isForward;
      Serial.print("EVENT: Direction switched to ");
      Serial.println(isForward ? "FORWARD" : "REVERSE");
      delay(150); // Button release debounce
    }
  }
  lastDirBtnState = dirBtnReading;

  // Debounce State Button
  if (stateBtnReading != lastStateBtnState) {
    lastDebounceState = currentMillis;
  }
  if ((currentMillis - lastDebounceState) > DEBOUNCE_DELAY) {
    if (stateBtnReading == HIGH && lastStateBtnState == LOW) {
      motorRunning = !motorRunning;
      Serial.print("EVENT: Motor state set to ");
      Serial.println(motorRunning ? "RUNNING" : "STOPPED");
      delay(150);
    }
  }
  lastStateBtnState = stateBtnReading;

  // Update hardware outputs
  updateMotorOutputs();

  // Output Status to Serial Monitor (log on changes, or throttle every 1000ms if running)
  bool changeDetected = (speedPct != lastSpeedPct) || 
                        (motorRunning != lastRunningState) || 
                        (isForward != lastDirectionState);
                        
  if (changeDetected || (motorRunning && (currentMillis - lastSerialPrint >= 1000))) {
    lastSerialPrint = currentMillis;
    lastSpeedPct = speedPct;
    lastRunningState = motorRunning;
    lastDirectionState = isForward;
    
    Serial.print("MOTOR STATUS: [");
    Serial.print(motorRunning ? "RUNNING" : "STOPPED");
    Serial.print("] | Direction: ");
    Serial.print(isForward ? "Forward" : "Reverse");
    Serial.print(" | Speed: ");
    Serial.print(speedPct);
    Serial.println("%");
  }
}

void updateMotorOutputs() {
  if (motorRunning) {
    // Write speed PWM
    analogWrite(ENA_PIN, rawSpeed);
    
    // Set direction pins
    if (isForward) {
      digitalWrite(IN1_PIN, HIGH);
      digitalWrite(IN2_PIN, LOW);
    } else {
      digitalWrite(IN1_PIN, LOW);
      digitalWrite(IN2_PIN, HIGH);
    }
  } else {
    // Stop motor (disable driver output)
    analogWrite(ENA_PIN, 0);
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
  }
}
