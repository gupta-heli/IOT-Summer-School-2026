/**
 * @file traffic_light.ino
 * @brief Traffic Light Controller with Pedestrian Override.
 *        RED (5s) -> YELLOW (2s) -> GREEN (4s).
 *        Pedestrian button on pin 7 forces RED immediately for 8 seconds.
 *        Current states are logged with timestamps (millis()).
 *        Course Coursework: Week 2, Assignment Q14
 */

const int RED_PIN = 10;
const int YELLOW_PIN = 11;
const int GREEN_PIN = 12;
const int BUTTON_PIN = 7;

enum TrafficState {
  STATE_RED,
  STATE_YELLOW,
  STATE_GREEN,
  STATE_PEDESTRIAN
};

TrafficState currentState = STATE_RED;
unsigned long stateStartTime = 0;
unsigned long stateDuration = 5000; // Start with RED for 5000ms

void setLights(bool red, bool yellow, bool green) {
  digitalWrite(RED_PIN, red ? HIGH : LOW);
  digitalWrite(YELLOW_PIN, yellow ? HIGH : LOW);
  digitalWrite(GREEN_PIN, green ? HIGH : LOW);
}

void printState(const char* stateName) {
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms] STATE: ");
  Serial.println(stateName);
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  // Hardware list specifies external pull-down resistors for buttons,
  // so a button press reads HIGH.
  pinMode(BUTTON_PIN, INPUT);
  
  Serial.begin(9600);
  
  stateStartTime = millis();
  setLights(true, false, false);
  printState("RED (Initial)");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Read pedestrian button (HIGH when pressed due to external pull-down)
  if (digitalRead(BUTTON_PIN) == HIGH && currentState != STATE_PEDESTRIAN) {
    currentState = STATE_PEDESTRIAN;
    stateStartTime = currentMillis;
    stateDuration = 8000;
    setLights(true, false, false);
    printState("PEDESTRIAN OVERRIDE (FORCED RED - 8s)");
    delay(200); // Debounce delay
  }
  
  // Check if current state duration has expired
  if (currentMillis - stateStartTime >= stateDuration) {
    stateStartTime = currentMillis;
    
    switch (currentState) {
      case STATE_RED:
        currentState = STATE_YELLOW;
        stateDuration = 2000;
        setLights(false, true, false);
        printState("YELLOW");
        break;
        
      case STATE_YELLOW:
        currentState = STATE_GREEN;
        stateDuration = 4000;
        setLights(false, false, true);
        printState("GREEN");
        break;
        
      case STATE_GREEN:
      case STATE_PEDESTRIAN:
        currentState = STATE_RED;
        stateDuration = 5000;
        setLights(true, false, false);
        printState("RED");
        break;
    }
  }
}
