# Smart Street Light Controller
*Course Coursework: Week 3, Assignment Q23*

This project simulates an energy-efficient smart street light using LDR and PIR sensors.

## Hardware Connections
- **LDR Input:** Pin A1
- **PIR Input:** Pin 2
- **LED Output (PWM):** Pin 9

## Operating Logic
1. **Daylight:** LED is completely OFF.
2. **Night (No Motion):** LED dims to 20% brightness to save energy.
3. **Night (Motion Detected):** LED turns ON at 100% brightness. Keeps 100% brightness for 30 seconds after last detected motion, then dims back to 20%.
