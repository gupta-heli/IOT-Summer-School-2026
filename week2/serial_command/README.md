# Serial Command Interface
*Course Coursework: Week 2, Assignment Q16*

This project parses serial commands to control Arduino hardware.

## Features
- **LED_ON:** Turns built-in LED (pin 13) ON.
- **LED_OFF:** Turns built-in LED OFF.
- **BLINK_X:** Blinks the LED X times (X must be 1 to 9).
- **STATUS:** Displays current LED pin state and total blink count.
- **RESET:** Resets cumulative blink counter to 0.

## Usage
Open the Serial Monitor at **9600 baud**, type any command (e.g., `BLINK_5`), and press Enter.
