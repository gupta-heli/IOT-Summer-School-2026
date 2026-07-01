# Traffic Light Controller with Pedestrian Override
*Course Coursework: Week 2, Assignment Q14*

This project simulates a street traffic light with a pedestrian request button.

## Pin Mappings
- **Red LED:** Pin 10
- **Yellow LED:** Pin 11
- **Green LED:** Pin 12
- **Pedestrian Button:** Pin 7

## How It Works
1. Runs a continuous state cycle: Red (5s) -> Yellow (2s) -> Green (4s).
2. Pressing the button on pin 7 immediately overrides the green/yellow lights, turning the Red LED ON and holding it for 8 seconds.
3. Outputs current state logs via Serial Monitor (9600 baud) with `millis()` timestamps.
