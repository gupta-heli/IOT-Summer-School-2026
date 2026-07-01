# Vending Machine Finite State Machine (FSM)
*Course Coursework: Week 2, Assignment Q18*

This project implements a finite state machine simulating a coin-operated vending machine.

## States
- **IDLE:** Waiting for coin. (Green LED ON)
- **COIN_INSERTED:** Coin inserted, waiting for item selection. (Yellow LED ON)
- **ITEM_SELECTED:** Item selected, preparing to dispense. (Red LED ON)
- **DISPENSING:** Dispensing item (LEDs blink), then returns to IDLE.

## Inputs
- **Insert Coin Button:** Pin 2
- **Select Item Button:** Pin 3
- **Cancel Button:** Pin 4
