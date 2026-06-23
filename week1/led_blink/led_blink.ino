/**
 * @file led_blink.ino
 * @author Heli Gupta
 * @date 2026-07-05
 * @brief Potentiometer-controlled LED blink with serial logging.
 *        This sketch reads an analog value from a potentiometer to adjust
 *        the blink rate of an LED connected to digital pin 13, and prints
 *        the current blink count and delay to the Serial Monitor.
 */

int blinkCount = 0;
const int potPin = A0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int potValue = analogRead(potPin);
  int delayTime = map(potValue, 0, 1023, 100, 2000);
  
  digitalWrite(13, HIGH);
  delay(delayTime);
  digitalWrite(13, LOW);
  delay(delayTime);
  blinkCount++;
  Serial.print("Blink count: ");
  Serial.print(blinkCount);
  Serial.print(" | Delay: ");
  Serial.println(delayTime);
}
