# Multi-Sensor Data Logger
*Course Coursework: Week 3, Assignment Q24*

This project reads three sensors simultaneously (DHT11, LDR, and HC-SR04) and outputs a structured log to the Serial Monitor every 5 seconds.

## Hardware Connections
- **DHT11 Data Pin:** Pin 2
- **LDR Analog Input:** Pin A1
- **HC-SR04 Trig Pin:** Pin 5
- **HC-SR04 Echo Pin:** Pin 6

## Sample Output Layout
```text
=== SENSOR LOG ===
Time      : 12345 ms
Temp      : 28.5 C | Humidity: 65%
Light     : 73% (Bright)
Distance  : 42 cm
==================
```
