# Password-Protected Keypad & LCD Access System
*Course Coursework: Week 3, Assignment Q28*

This project implements a secure access system using a 4x4 matrix keypad and an I2C 16x2 LCD.

## Pin Mappings
- **Keypad Rows:** Pins 9, 8, 7, 6
- **Keypad Columns:** Pins 5, 4, 3, 2
- **I2C LCD:** Pins SDA (A4) and SCL (A5)
- **Green LED (Success):** Pin 12
- **Red LED (Alarm):** Pin 13
- **Buzzer (Alarm):** Pin 11

## Features
1. **Default PIN:** `1234`
2. **Access Granted:** LCD displays greeting, Green LED lights up, and a positive confirmation beep sounds.
3. **Access Denied:** LCD displays warning, Red LED lights up, and a warning tone sounds.
4. **Lockout:** After 3 consecutive wrong attempts, the system locks down for 10 seconds, showing a countdown timer on the screen.
