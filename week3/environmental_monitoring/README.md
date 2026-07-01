# Environmental Monitoring Station
*Course Coursework: Week 3, Assignment Q21*

This project measures temperature and humidity using a DHT11 sensor and logs data.

## Hardware Connections
- **DHT11 Data Pin:** Pin 2
- **Red LED Pin (Alarm):** Pin 11
- **Green LED Pin (Normal):** Pin 12

## Parameters & Thresholds
- Data logged in CSV format: `timestamp,temp_C,temp_F,humidity`
- Alarm triggers if temperature > 35°C OR humidity > 80% (Red LED turns ON, Green turns OFF).

## Library Version
- **DHT Sensor Library by Adafruit:** Version 1.4.6 (or latest)
