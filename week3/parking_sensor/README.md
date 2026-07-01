# Ultrasonic Parking Sensor System
*Course Coursework: Week 3, Assignment Q22*

This project simulates a vehicle parking sensor using an HC-SR04 ultrasonic sensor.

## Hardware Connections
- **HC-SR04 Trig Pin:** Pin 5
- **HC-SR04 Echo Pin:** Pin 6
- **Green LED Pin:** Pin 8
- **Yellow LED Pin:** Pin 9
- **Red LED Pin:** Pin 10
- **Buzzer Pin:** Pin 11

## Alert Levels
- **Distance > 50cm:** SAFE (Green LED ON, buzzer OFF).
- **Distance 20-50cm:** WARNING (Yellow LED ON, buzzer beeps every 500ms).
- **Distance 10-20cm:** ALERT (Red LED ON, buzzer beeps every 200ms).
- **Distance < 10cm:** CRITICAL (All LEDs flash rapidly, buzzer continuous).
