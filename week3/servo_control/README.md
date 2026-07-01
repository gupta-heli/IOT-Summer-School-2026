# Servo Motor Sweep & Potentiometer Control
*Course Coursework: Week 3, Assignment Q25*

This project controls an SG90 servo motor using a potentiometer or a button trigger.

## Hardware Connections
- **Potentiometer Input:** Pin A0
- **Push Button Input:** Pin 2
- **Servo Signal Pin:** Pin 9

## Operating Modes
1. **Potentiometer Control:** Rotating the potentiometer mapped (0-1023) directly adjusts the servo position from 0° to 180°.
2. **Sweep Mode:** Pressing the button on pin 2 makes the servo perform a full sweep from 0° to 180° and back to 0° at a steady rate.
