# PWM Fading Night Light
*Course Coursework: Week 2, Assignment Q17*

This project simulates a smart breathing night light with an SOS emergency signal.

## Pin Mappings
- **LED Output (PWM):** Pin 9
- **Button input:** Pin 2

## Modes
1. **Slow Breathing (3-second cycle):** LED fades in and out continuously using a triangle wave.
2. **Fast Pulse (0.5-second cycle):** LED pulses rapidly.
3. **SOS Morse Code:** LED blinks out the `... --- ...` pattern in a non-blocking sequence.
