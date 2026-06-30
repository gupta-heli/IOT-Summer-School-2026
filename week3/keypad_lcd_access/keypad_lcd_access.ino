/**
 * @file keypad_lcd_access.ino
 * @brief Password-Protected Access System using Keypad & I2C 16x2 LCD.
 *        - LCD displays "ENTER PIN:".
 *        - User enters 4-digit PIN using a 4x4 keypad.
 *        - Correct PIN ("1234") -> displays "ACCESS GRANTED" + Green LED (pin 12).
 *        - Incorrect PIN -> displays "ACCESS DENIED" + Red LED (pin 13) + Buzzer (pin 11).
 *        - After 3 incorrect attempts, the system locks out for 10 seconds.
 *        - Displays countdown on LCD during lockout.
 *        Course Coursework: Week 3, Assignment Q28
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// PIN Definitions
const int LED_GREEN = 12;
const int LED_RED = 13;
const int BUZZER_PIN = 11;

// Keypad Configuration
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Connect row pins of keypad to Arduino digital pins
byte rowPins[ROWS] = {9, 8, 7, 6}; 
// Connect column pins of keypad to Arduino digital pins
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LCD Configuration (I2C address 0x27 or 0x3F, 16 columns and 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Password settings
const String CORRECT_PIN = "1234";
String enteredPin = "";
int wrongAttempts = 0;
bool isLocked = false;
unsigned long lockoutStart = 0;
const unsigned long LOCKOUT_DURATION = 10000; // 10 seconds lockout

void resetSystem() {
  enteredPin = "";
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  noTone(BUZZER_PIN);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENTER PIN:");
  lcd.setCursor(0, 1);
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  resetSystem();
  Serial.println("Access Control System Online. Default PIN: 1234");
}

void loop() {
  unsigned long currentMillis = millis();

  // If system is currently locked out
  if (isLocked) {
    unsigned long elapsed = currentMillis - lockoutStart;
    if (elapsed >= LOCKOUT_DURATION) {
      // Lockout expired
      isLocked = false;
      wrongAttempts = 0;
      Serial.println("EVENT: Lockout expired. System reset.");
      resetSystem();
    } else {
      // Show remaining time
      int remaining = (LOCKOUT_DURATION - elapsed) / 1000;
      static int lastRemaining = -1;
      
      if (remaining != lastRemaining) {
        lastRemaining = remaining;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SYSTEM LOCKED!");
        lcd.setCursor(0, 1);
        lcd.print("Wait ");
        lcd.print(remaining);
        lcd.print(" seconds...");
        
        Serial.print("LOG: System Locked. Remaining time: ");
        Serial.print(remaining);
        Serial.println("s");
        
        // Sound warning buzzer beep on each second
        tone(BUZZER_PIN, 500, 100);
        digitalWrite(LED_RED, HIGH);
        delay(100);
        digitalWrite(LED_RED, LOW);
      }
    }
    return; // Skip keypad reading during lockout
  }

  // Normal keypad scanning
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Key pressed: ");
    Serial.println(key);
    
    // Reset/Clear command (using '*')
    if (key == '*') {
      resetSystem();
      return;
    }
    
    // Accept only numeric keys
    if (key >= '0' && key <= '9') {
      enteredPin += key;
      
      // Update LCD display
      lcd.setCursor(enteredPin.length() - 1, 1);
      lcd.print('*'); // Obfuscate password entry
      
      // Check if 4 digits have been entered
      if (enteredPin.length() == 4) {
        delay(300); // Small pause to show the final '*'
        
        if (enteredPin == CORRECT_PIN) {
          // --- ACCESS GRANTED ---
          Serial.println("EVENT: Access GRANTED.");
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("ACCESS GRANTED!");
          lcd.setCursor(0, 1);
          lcd.print("Welcome home!");
          
          digitalWrite(LED_GREEN, HIGH);
          digitalWrite(LED_RED, LOW);
          tone(BUZZER_PIN, 2000, 500); // Confirmed beep
          
          delay(3000); // Keep screen up for 3 seconds
          resetSystem();
        } 
        else {
          // --- ACCESS DENIED ---
          wrongAttempts++;
          Serial.print("EVENT: Access DENIED. Attempt count: ");
          Serial.println(wrongAttempts);
          
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("ACCESS DENIED!");
          lcd.setCursor(0, 1);
          lcd.print("Try again!");
          
          digitalWrite(LED_GREEN, LOW);
          digitalWrite(LED_RED, HIGH);
          
          // Sound alarm buzzer
          tone(BUZZER_PIN, 800, 1000); // 1-second warning tone
          delay(1000);
          
          if (wrongAttempts >= 3) {
            // Lockout triggered
            isLocked = true;
            lockoutStart = millis();
            Serial.println("EVENT: Max wrong attempts reached. System locked out!");
          } else {
            resetSystem();
          }
        }
      }
    }
  }
}
