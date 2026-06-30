/**
 * @file servo_control.ino
 * @brief Servo Motor Control via Potentiometer & Push Button.
 *        - Reads potentiometer on A0 to control SG90 servo angle (0-180°).
 *        - A push button on pin 2 triggers a full sweep: 0° -> 180° -> 0°.
 *        - Displays the current angle and sweep events on the Serial Monitor.
 *        Course Coursework: Week 3, Assignment Q25
 */

#include <Servo.h>

const int POT_PIN = A0;      // Potentiometer Analog input
const int BTN_PIN = 2;       // Push Button Digital input
const int SERVO_PIN = 9;     // Servo Signal pin

Servo myServo;

int lastAngle = -1;
unsigned long lastSerialPrint = 0;

void setup() {
  myServo.attach(SERVO_PIN);
  pinMode(BTN_PIN, INPUT); // External pull-down resistor
  Serial.begin(9600);
  
  Serial.println("Servo Control System Initialized.");
  Serial.println("Rotate the potentiometer to control angle, or press the button to sweep.");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Read button state
  bool btnPressed = (digitalRead(BTN_PIN) == HIGH);
  
  if (btnPressed) {
    // Perform manual sweep
    Serial.println("EVENT: Button Pressed. Executing full sweep (0 -> 180 -> 0)...");
    
    // Sweep from 0 to 180 degrees
    for (int angle = 0; angle <= 180; angle++) {
      myServo.write(angle);
      Serial.print("Sweep Angle: ");
      Serial.print(angle);
      Serial.println(" deg");
      delay(15); // Wait 15ms for servo to reach position
    }
    
    delay(200); // Pause at 180
    
    // Sweep back from 180 to 0 degrees
    for (int angle = 180; angle >= 0; angle--) {
      myServo.write(angle);
      Serial.print("Sweep Angle: ");
      Serial.print(angle);
      Serial.println(" deg");
      delay(15);
    }
    
    Serial.println("EVENT: Sweep Complete. Resuming potentiometer control.");
    delay(300); // Debounce delay
    lastAngle = -1; // Reset last angle tracker
  } 
  else {
    // Normal potentiometer control mode
    int potValue = analogRead(POT_PIN);
    // Map potentiometer values (0-1023) to angles (0-180)
    int currentAngle = map(potValue, 0, 1023, 0, 180);
    
    // Write and update only if angle changes by more than 1 degree to reduce jitter
    if (abs(currentAngle - lastAngle) > 1) {
      myServo.write(currentAngle);
      lastAngle = currentAngle;
      
      // Throttle Serial logging to prevent spamming
      if (currentMillis - lastSerialPrint >= 500) {
        lastSerialPrint = currentMillis;
        Serial.print("Potentiometer Angle: ");
        Serial.print(currentAngle);
        Serial.println(" deg");
      }
    }
  }
  
  delay(20); // Small loop delay
}
