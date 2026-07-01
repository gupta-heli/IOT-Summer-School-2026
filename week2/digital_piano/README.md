# 4-Key Digital Piano with Scale Toggle
*Course Coursework: Week 2, Assignment Q15*

This project creates a basic 4-key musical instrument using push buttons and a passive buzzer.

## Pin Mappings
- **Do Button:** Pin 2 (262 Hz)
- **Re Button:** Pin 3 (294 Hz)
- **Mi/Me Button:** Pin 4 (330 Hz / 311 Hz)
- **Fa Button:** Pin 5 (349 Hz)
- **Scale Toggle Button:** Pin 6
- **Buzzer Output:** Pin 9

## How It Works
1. Pressing buttons 1-4 plays Do, Re, Mi, Fa. Releasing silences it.
2. Pressing two or more buttons together plays Sol (392 Hz) as a chord substitute.
3. Pressing the 5th button toggles between Major and Minor scales (changing the third note from 330 Hz to 311 Hz).
