# DC Motor Control via L298N Driver
*Course Coursework: Week 3, Assignment Q26*

This project regulates the speed, direction, and state of a DC motor using an L298N motor driver.

## Pin Mappings
- **L298N ENA (PWM Speed):** Pin 9
- **L298N IN1 (Direction 1):** Pin 7
- **L298N IN2 (Direction 2):** Pin 8
- **Potentiometer Input:** Pin A0
- **Direction Toggle Button:** Pin 2
- **State Toggle (Start/Stop) Button:** Pin 3

## Status Logging
Logs the current running state (`RUNNING` / `STOPPED`), speed percentage (`0-100%`), and direction (`Forward` / `Reverse`) to the Serial Monitor.
