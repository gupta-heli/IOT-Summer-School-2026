/**
 * @file serial_command.ino
 * @brief Serial Command Interface.
 *        Receives commands over Serial Monitor to control built-in LED (pin 13):
 *        - LED_ON  -> Turns built-in LED ON
 *        - LED_OFF -> Turns built-in LED OFF
 *        - BLINK_X -> Blinks LED X times (X is 1 to 9)
 *        - STATUS  -> Prints LED pin state and total blink count
 *        - RESET   -> Resets the total blink counter to 0
 *        Unknown commands display input validation errors.
 *        Course Coursework: Week 2, Assignment Q16
 */

const int LED_PIN = LED_BUILTIN; // Built-in LED on pin 13
long totalBlinks = 0;
String inputString = "";         // A String to hold incoming data
bool stringComplete = false;     // Whether the string is complete

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Start with LED off
  Serial.begin(9600);
  
  // Reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  Serial.println("===========================================");
  Serial.println("Serial Command Interface Ready.");
  Serial.println("Supported commands: LED_ON, LED_OFF, BLINK_X, STATUS, RESET");
  Serial.println("===========================================");
}

void loop() {
  // Read serial input when available
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    
    // If the incoming character is a newline or carriage return, set flag
    if (inChar == '\n' || inChar == '\r') {
      if (inputString.length() > 0) {
        stringComplete = true;
      }
    } else {
      // Add it to the inputString:
      inputString += inChar;
    }
  }

  // Handle command when complete
  if (stringComplete) {
    inputString.trim(); // Remove leading/trailing whitespaces
    
    if (inputString == "LED_ON") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("SUCCESS: Built-in LED turned ON");
    } 
    else if (inputString == "LED_OFF") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("SUCCESS: Built-in LED turned OFF");
    } 
    else if (inputString == "STATUS") {
      bool ledState = digitalRead(LED_PIN);
      Serial.println("----- STATUS REPORT -----");
      Serial.print("LED State: ");
      Serial.println(ledState ? "HIGH (ON)" : "LOW (OFF)");
      Serial.print("Total Blinks Count: ");
      Serial.println(totalBlinks);
      Serial.println("-------------------------");
    } 
    else if (inputString == "RESET") {
      totalBlinks = 0;
      Serial.println("SUCCESS: Blink counter reset to 0");
    } 
    else if (inputString.startsWith("BLINK_")) {
      // Check if command is exactly 7 characters (BLINK_X)
      if (inputString.length() == 7) {
        char numChar = inputString.charAt(6);
        if (numChar >= '1' && numChar <= '9') {
          int blinkTimes = numChar - '0';
          
          Serial.print("SUCCESS: Blinking LED ");
          Serial.print(blinkTimes);
          Serial.println(" times...");
          
          // Perform blinking
          for (int i = 0; i < blinkTimes; i++) {
            digitalWrite(LED_PIN, HIGH);
            delay(200);
            digitalWrite(LED_PIN, LOW);
            delay(200);
          }
          
          totalBlinks += blinkTimes;
          Serial.print("Blinking complete. Total blinks in session: ");
          Serial.println(totalBlinks);
        } else {
          Serial.println("ERROR: Invalid blink count. Must be between 1 and 9 (e.g., BLINK_5)");
        }
      } else {
        Serial.println("ERROR: Unknown command format. Did you mean BLINK_X?");
      }
    } 
    else {
      Serial.print("ERROR: Unknown command '");
      Serial.print(inputString);
      Serial.println("'");
    }
    
    // Clear the string for the next command:
    inputString = "";
    stringComplete = false;
  }
}
