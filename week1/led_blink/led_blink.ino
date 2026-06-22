int blinkCount = 0;
const int potPin = A0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int potValue = analogRead(potPin);
  // Potentiometer value is 0-1023, map it to a reasonable delay range (100ms to 2000ms)
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
