# Project: Potentiometer-Controlled LED Blink with Serial Logging
*Course Coursework: Week 1, Assignment Q5*

This project demonstrates how to control the blinking frequency of an LED using a potentiometer. It also tracks the total number of blinks and sends this information, along with the current delay interval in milliseconds, back to the PC via the Serial Monitor.

---

## 🛠️ Hardware Required
- 1x Arduino UNO (or compatible microcontroller)
- 1x LED (Red/Green/Blue)
- 1x 220Ω Resistor (for current limiting)
- 1x 10kΩ Potentiometer (rotary)
- 1x Breadboard
- Jumper Wires (M-M)

---

## 🔌 Circuit Diagram Description (Text-Based)
1. **LED Connection:**
   - **Anode (Longer leg)** of the LED connected to digital pin **D13** on the Arduino via a **220Ω resistor**.
   - **Cathode (Shorter leg)** of the LED connected directly to the Arduino's ground (**GND**).

2. **Potentiometer Connection:**
   - **Left pin (Pin 1)** connected to the Arduino's **5V** pin.
   - **Middle pin (Pin 2 / Wiper)** connected to the Arduino's analog input pin **A0**.
   - **Right pin (Pin 3)** connected to the Arduino's ground (**GND**).

---

## 🚀 How to Upload Code
Follow these steps to upload the code to your Arduino Board using the Arduino IDE:
1. Open the **Arduino IDE** on your computer.
2. Open the file `led_blink.ino` located in the `/week1/led_blink/` folder.
3. Connect your Arduino board to your computer using a USB cable.
4. Go to **Tools > Board** and select your board model (e.g., *Arduino Uno*).
5. Go to **Tools > Port** and select the active COM port (e.g., *COM3* or *COM4*).
6. Click the **Upload** button (the right arrow icon in the toolbar) or press `Ctrl + U` (`Cmd + U` on Mac).
7. Wait for the status bar at the bottom to display **Done uploading**.

---

## 🖥️ Expected Output
1. The LED connected to D13 will blink.
2. Rotating the potentiometer knob:
   - **Clockwise (higher voltage):** Increases the delay up to `2000 ms` (slower blinking).
   - **Counter-clockwise (lower voltage):** Decreases the delay down to `100 ms` (faster blinking).
3. Open the **Serial Monitor** (set baud rate to **9600**) to see output formatted like:
   ```text
   Blink count: 1 | Delay: 540
   Blink count: 2 | Delay: 540
   Blink count: 3 | Delay: 980
   Blink count: 4 | Delay: 1210
   ```

---

## 🔍 Troubleshooting Tips
- **Issue 1: The LED is not blinking at all.**
  * *Solution:* Check if the LED is inserted in the correct orientation. The longer leg (Anode) must connect to pin 13 and the shorter leg (Cathode) to GND. Also, ensure the resistor is securely connected.
- **Issue 2: The blink speed does not change when turning the potentiometer.**
  * *Solution:* Verify that the wiper (middle pin) of the potentiometer is connected to analog pin **A0** (not digital pin 0). Double-check the 5V and GND connections on the outer pins of the potentiometer.
- **Issue 3: Serial Monitor is showing gibberish/weird symbols.**
  * *Solution:* Ensure that the baud rate dropdown in the bottom right corner of the Serial Monitor window is set to **9600 baud**, which matches the `Serial.begin(9600)` statement in the setup function.
