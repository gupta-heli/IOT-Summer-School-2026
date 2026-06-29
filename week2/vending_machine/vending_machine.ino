/**
 * @file vending_machine.ino
 * @brief Simple Vending Machine State Machine.
 * 
 * State Transition Diagram:
 * 
 *          +--------------------------------------------------------+
 *          |                                                        | (Dispensing
 *          |                      +-----------------+               |  Complete)
 *          |                      |      IDLE       | <-------------+
 *          |                      +-----------------+
 *          |                        |
 *          |                        | [Insert Coin]
 *          |                        v
 *          |     [Cancel]         +-----------------+
 *          +--------------------- |  COIN_INSERTED  |
 *          |                      +-----------------+
 *          |                        |
 *          |                        | [Select Item]
 *          |                        v
 *          |     [Cancel]         +-----------------+
 *          +--------------------- |  ITEM_SELECTED  |
 *                                 +-----------------+
 *                                   |
 *                                   | (Auto-timeout after 1.5s)
 *                                   v
 *                                 +-----------------+
 *                                 |   DISPENSING    |
 *                                 +-----------------+
 * 
 * Hardware Mappings:
 * - Inputs:
 *   - Button 1 (Pin 2): Insert Coin
 *   - Button 2 (Pin 3): Select Item
 *   - Button 3 (Pin 4): Cancel
 * - Outputs:
 *   - LED 1 (Pin 10): State indicator 1 (Green)
 *   - LED 2 (Pin 11): State indicator 2 (Yellow)
 *   - LED 3 (Pin 12): State indicator 3 (Red)
 * 
 * Course Coursework: Week 2, Assignment Q18
 */

// Pin Definitions
const int BTN_COIN = 2;
const int BTN_SELECT = 3;
const int BTN_CANCEL = 4;

const int LED_GREEN = 10;
const int LED_YELLOW = 11;
const int LED_RED = 12;

// State Enum
enum VendingState {
  STATE_IDLE,
  STATE_COIN_INSERTED,
  STATE_ITEM_SELECTED,
  STATE_DISPENSING
};

VendingState currentState = STATE_IDLE;
unsigned long stateTimer = 0;
const unsigned long SELECTION_TIMEOUT = 1500; // 1.5s to cancel select before dispensing
const unsigned long DISPENSE_TIME = 2000;    // 2s dispensing action

void setLEDs(bool green, bool yellow, bool red) {
  digitalWrite(LED_GREEN, green ? HIGH : LOW);
  digitalWrite(LED_YELLOW, yellow ? HIGH : LOW);
  digitalWrite(LED_RED, red ? HIGH : LOW);
}

void transitionTo(VendingState newState) {
  currentState = newState;
  stateTimer = millis();
  
  Serial.print("[");
  Serial.print(stateTimer);
  Serial.print(" ms] TRANSITION: New State is ");
  
  switch (currentState) {
    case STATE_IDLE:
      Serial.println("IDLE (Ready for coin)");
      setLEDs(true, false, false); // Green LED ON
      break;
    case STATE_COIN_INSERTED:
      Serial.println("COIN_INSERTED (Select item or cancel)");
      setLEDs(false, true, false); // Yellow LED ON
      break;
    case STATE_ITEM_SELECTED:
      Serial.println("ITEM_SELECTED (Preparing dispensing...)");
      setLEDs(false, false, true); // Red LED ON
      break;
    case STATE_DISPENSING:
      Serial.println("DISPENSING (Please wait...)");
      setLEDs(true, true, true);  // All LEDs ON
      break;
  }
}

void setup() {
  pinMode(BTN_COIN, INPUT);
  pinMode(BTN_SELECT, INPUT);
  pinMode(BTN_CANCEL, INPUT);
  
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  Serial.begin(9600);
  transitionTo(STATE_IDLE);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Read inputs (HIGH when pressed, due to pull-down resistors)
  bool coinPressed = (digitalRead(BTN_COIN) == HIGH);
  bool selectPressed = (digitalRead(BTN_SELECT) == HIGH);
  bool cancelPressed = (digitalRead(BTN_CANCEL) == HIGH);

  // Vending Machine State Logic
  switch (currentState) {
    case STATE_IDLE:
      if (coinPressed) {
        transitionTo(STATE_COIN_INSERTED);
        delay(200); // Debounce
      }
      break;
      
    case STATE_COIN_INSERTED:
      if (cancelPressed) {
        Serial.println("EVENT: Transaction Cancelled. Refunding coin.");
        transitionTo(STATE_IDLE);
        delay(200); // Debounce
      } else if (selectPressed) {
        transitionTo(STATE_ITEM_SELECTED);
        delay(200); // Debounce
      }
      break;
      
    case STATE_ITEM_SELECTED:
      if (cancelPressed) {
        Serial.println("EVENT: Selection Cancelled. Refunding coin.");
        transitionTo(STATE_IDLE);
        delay(200); // Debounce
      } 
      // Auto transition to Dispensing after selection timeout
      else if (currentMillis - stateTimer >= SELECTION_TIMEOUT) {
        transitionTo(STATE_DISPENSING);
      }
      break;
      
    case STATE_DISPENSING:
      // Blink LEDs to simulate motor activity/dispensing
      if ((currentMillis / 200) % 2 == 0) {
        setLEDs(true, true, true);
      } else {
        setLEDs(false, false, false);
      }
      
      // Auto transition back to IDLE after dispensing is complete
      if (currentMillis - stateTimer >= DISPENSE_TIME) {
        Serial.println("EVENT: Item Dispensed. Thank you!");
        transitionTo(STATE_IDLE);
      }
      break;
  }
}
