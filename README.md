# SwitchLed — TM4C123GH6PM

A simple program that allows user to turn on a LED with a Switch on a breadboard.

The LED is on while the switch is pressed and off when it is released.

## Environment
Project is build with Code Compose Studio(Theia) using GNU Arm Toolchain and CMSIS.

## Hardware
- Switch(Pushbutton)
- Red LED
- Resistors (220 Ohm, 10kOhm)
- Breadboard

## Requirements
- Code Composer Studio (CCS) installed
- GNU Arm Toolchain installed and added to the CCS

## Usage
1. Wire the LED, Switch and resistors on the breadboard and connect to the MCU as shown on the picture.
1. Open the SwitchLed project in CCS.
2. Flash the code to the board.
3. Press the Switch and hold to light the LED on. Release the Switch to light the LED off.
