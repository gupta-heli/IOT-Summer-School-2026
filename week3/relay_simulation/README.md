# Relay-Controlled AC Device Hysteresis Simulator
*Course Coursework: Week 3, Assignment Q27*

This project simulates a thermal control system (like an AC unit) using a temperature sensor, a relay, and a override switch.

## Pin Mappings
- **DHT11 Data Pin:** Pin 2
- **Relay Signal (LED):** Pin 8
- **Override Button:** Pin 3

## Hysteresis Logic
1. **Temp > 32°C:** Relay turns ON (AC active).
2. **Temp < 28°C:** Relay turns OFF (AC idle).
3. **28°C to 32°C:** Relay maintains previous state.
4. **Manual Override:** Short-pressing the button toggles the relay state manually and locks the system in manual mode. Long-pressing (2 seconds) restores automatic control.
