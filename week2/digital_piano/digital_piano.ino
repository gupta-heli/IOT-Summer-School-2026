/**
 * @file digital_piano.ino
 * @brief Digital Piano - Step 3: Scale Toggle (Major / Minor).
 *        If two or more buttons are pressed together: play Sol (392Hz).
 *        A 5th button on pin 6 toggles between Major and Minor scales.
 *        In Minor scale, Mi (330Hz) becomes Me/Eb (311Hz).
 *        Buttons on pins 2, 3, 4, and 5 play Do, Re, Mi/Me, Fa.
 *        Passive buzzer on pin 9.
 *        Course Coursework: Week 2, Assignment Q15
 */

const int BUZZER_PIN = 9;
const int BTN_DO = 2;
const int BTN_RE = 3;
const int BTN_MI = 4;
const int BTN_FA = 5;
const int BTN_TOGGLE = 6; // 5th button for Major/Minor toggle

// Frequencies for Major scale
const int NOTE_DO = 262; // Hz
const int NOTE_RE = 294; // Hz
const int NOTE_MI_MAJ = 330; // Hz (Mi in Major)
const int NOTE_MI_MIN = 311; // Hz (Me/Eb in Minor)
const int NOTE_FA = 349; // Hz
const int NOTE_SOL = 392; // Hz (Chord substitute)

bool isMajorScale = true;
bool lastToggleState = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 50;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_DO, INPUT);
  pinMode(BTN_RE, INPUT);
  pinMode(BTN_MI, INPUT);
  pinMode(BTN_FA, INPUT);
  pinMode(BTN_TOGGLE, INPUT);
  Serial.begin(9600);
  Serial.println("System Ready: Scale set to MAJOR");
}

void loop() {
  unsigned long currentMillis = millis();

  // Read toggle button with debouncing
  bool toggleReading = digitalRead(BTN_TOGGLE);
  if (toggleReading != lastToggleState) {
    lastDebounceTime = currentMillis;
  }
  
  if ((currentMillis - lastDebounceTime) > DEBOUNCE_DELAY) {
    // If the button state has changed and is now HIGH
    if (toggleReading == HIGH && lastToggleState == LOW) {
      isMajorScale = !isMajorScale;
      Serial.print("Scale changed to: ");
      Serial.println(isMajorScale ? "MAJOR" : "MINOR");
      delay(200); // Prevent double-triggering
    }
  }
  lastToggleState = toggleReading;

  // Read note button states (HIGH when pressed, due to pull-down resistors)
  bool doPressed = (digitalRead(BTN_DO) == HIGH);
  bool rePressed = (digitalRead(BTN_RE) == HIGH);
  bool miPressed = (digitalRead(BTN_MI) == HIGH);
  bool faPressed = (digitalRead(BTN_FA) == HIGH);

  // Count how many buttons are pressed simultaneously
  int pressedCount = (doPressed ? 1 : 0) + 
                     (rePressed ? 1 : 0) + 
                     (miPressed ? 1 : 0) + 
                     (faPressed ? 1 : 0);

  // Determine actual frequency for the 3rd key based on active scale
  int activeMiFreq = isMajorScale ? NOTE_MI_MAJ : NOTE_MI_MIN;

  if (pressedCount >= 2) {
    // Chord substitute
    tone(BUZZER_PIN, NOTE_SOL);
    Serial.println("Playing: Sol (392Hz) [CHORD]");
  } else if (doPressed) {
    tone(BUZZER_PIN, NOTE_DO);
    Serial.print("Playing: Do (262Hz) - ");
    Serial.println(isMajorScale ? "Major" : "Minor");
  } else if (rePressed) {
    tone(BUZZER_PIN, NOTE_RE);
    Serial.print("Playing: Re (294Hz) - ");
    Serial.println(isMajorScale ? "Major" : "Minor");
  } else if (miPressed) {
    tone(BUZZER_PIN, activeMiFreq);
    Serial.print("Playing: ");
    Serial.print(isMajorScale ? "Mi (330Hz) - Major" : "Me (311Hz) - Minor");
    Serial.println();
  } else if (faPressed) {
    tone(BUZZER_PIN, NOTE_FA);
    Serial.print("Playing: Fa (349Hz) - ");
    Serial.println(isMajorScale ? "Major" : "Minor");
  } else {
    noTone(BUZZER_PIN);
  }
  delay(30); // Small delay for stability
}
