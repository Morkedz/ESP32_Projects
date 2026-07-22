# ESP32 Project Storage

This repository serves as a centralized storage location for various ESP32 development projects. The current implementation includes a simple project for controlling a TowerPro MG90S micro servo motor via GPIO 25 using the Arduino IDE.

## Getting Started

### Prerequisites

* Arduino IDE (v2.x recommended)
* ESP32 Board Core installed via the Boards Manager
* ESP32Servo Library by Kevin Harrington (Install via Sketch > Include Library > Manage Libraries)

Note: If using ESP32 Arduino Core v3.0+, ensure the ESP32Servo library is updated to prevent compilation errors regarding esp32-hal-ledc.h.

---

## Hardware Setup and Wiring

| Servo Wire Color | Description | ESP32 Connection |
| --- | --- | --- |
| Brown | Ground | GND |
| Red | Power (4.8V - 6V) | VIN (or external 5V source) |
| Orange/Yellow | PWM Signal | GPIO 25 (D25) |

---

## Installation and Flashing

1. Clone or download this repository.
2. Open the desired project file in your Arduino IDE.
3. Select the appropriate ESP32 board configuration via Tools > Board.
4. Select the correct serial port via Tools > Port.
5. Click Upload.