# Smart Street Light Circuit Diagram
*Course Coursework: Week 3, Assignment Q23*

This document provides a text-based circuit diagram and pin wiring details for the LDR + PIR Smart Street Light project.

---

## 📌 Pin Connection Table

| Component | Component Pin | Arduino Uno Pin | Description |
| :--- | :--- | :--- | :--- |
| **LDR (Light Sensor)** | Terminal 1 | **A1** | Analog input connected with a 10kΩ pull-down resistor to GND. |
| | Terminal 2 | **5V** | Direct power input. |
| **PIR (Motion Sensor)** | VCC | **5V** | Power supply (5V). |
| | GND | **GND** | Ground reference. |
| | OUT | **D2** | Digital output trigger. |
| **LED (Street Light)** | Anode (+) | **D9** | PWM output via a 220Ω resistor. |
| | Cathode (-) | **GND** | Common ground. |

---

## 🔌 Circuit Schematic (ASCII Representation)

```text
       +---------------------------------------------+
       |                 ARDUINO UNO                 |
       |                                             |
       |     5V    GND    A1     D2     D9 (PWM)     |
       +-----+------+-----+------+------+------------+
             |      |     |      |      |
             |      |     |      |      +------[ 220Ω Resistor ]----+
             |      |     |      |                                  |
             |      |     |      +-----------------+                |
             |      |     |                        |                |
             |      |     +------+                 |                |
             |      |            |                 |                |
             |      |            |                 v                v
             |      |        [ LDR Sensor ]   [ PIR Sensor ]     [ LED ]
             |      |            |  |             |  |           |  |
             |      |     +------+  |             |  |           |  |
             |      |     |         |             |  |           |  |
             |      +-----+----[10kΩ]             |  |           |  |
             |            |                       |  |           |  |
             +------------+-----------------------+  |           |  |
                          |                          |           |  |
                          +--------------------------+-----------+--+
                                                     |
                                                    GND
```

### Circuit Wiring Explanations:
1. **LDR Sensor:** Connected in a voltage-divider configuration. One terminal connects to 5V. The other terminal connects to A1 and also connects to GND through a **10kΩ resistor**. As light decreases, the resistance of the LDR increases, lowering the voltage read at pin **A1**.
2. **PIR Sensor:** Powered by 5V and GND. Its OUT pin is connected directly to digital pin **D2** on the Arduino. When motion is detected, the PIR pulls this pin HIGH.
3. **LED (Street Light):** Connected to PWM-enabled pin **D9** through a **220Ω current-limiting resistor** to GND. This allows the brightness of the LED to be faded between 100% and 20% using the `analogWrite()` function.
