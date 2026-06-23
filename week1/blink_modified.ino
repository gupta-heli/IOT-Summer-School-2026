/**
 * @file blink_modified.ino
 * @brief Blinks the LED 3 times fast, then pauses for 2 seconds.
 *        Designed for collaborative coursework assignment Q7.
 */

const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Blink 3 times fast (200ms ON, 200ms OFF)
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  
  // Pause for 2 seconds
  delay(2000);
}
