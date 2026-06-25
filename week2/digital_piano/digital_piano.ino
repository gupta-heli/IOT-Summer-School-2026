/**
 * @file digital_piano.ino
 * @brief Digital Piano - Step 1: Basic 4-Key Piano.
 *        Buttons on pins 2, 3, 4, and 5 play Do, Re, Mi, Fa.
 *        Passive buzzer on pin 9.
 *        Course Coursework: Week 2, Assignment Q15
 */

const int BUZZER_PIN = 9;
const int BTN_DO = 2;
const int BTN_RE = 3;
const int BTN_MI = 4;
const int BTN_FA = 5;

// Frequencies for Major scale
const int NOTE_DO = 262; // Hz
const int NOTE_RE = 294; // Hz
const int NOTE_MI = 330; // Hz
const int NOTE_FA = 349; // Hz

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_DO, INPUT);
  pinMode(BTN_RE, INPUT);
  pinMode(BTN_MI, INPUT);
  pinMode(BTN_FA, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Read button states (HIGH when pressed, due to pull-down resistors)
  bool doPressed = (digitalRead(BTN_DO) == HIGH);
  bool rePressed = (digitalRead(BTN_RE) == HIGH);
  bool miPressed = (digitalRead(BTN_MI) == HIGH);
  bool faPressed = (digitalRead(BTN_FA) == HIGH);

  if (doPressed) {
    tone(BUZZER_PIN, NOTE_DO);
    Serial.println("Playing: Do (262Hz)");
  } else if (rePressed) {
    tone(BUZZER_PIN, NOTE_RE);
    Serial.println("Playing: Re (294Hz)");
  } else if (miPressed) {
    tone(BUZZER_PIN, NOTE_MI);
    Serial.println("Playing: Mi (330Hz)");
  } else if (faPressed) {
    tone(BUZZER_PIN, NOTE_FA);
    Serial.println("Playing: Fa (349Hz)");
  } else {
    noTone(BUZZER_PIN);
  }
  delay(50); // Small delay for loop stability
}
