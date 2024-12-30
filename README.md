
# Home Automation with RFID Access Control

This project is an Arduino-based home automation system integrated with an RC522 RFID module for secure door access control. 
The system also includes features like light control based on room occupancy.

## Features

- **RFID Door Access Control:** Uses an RC522 RFID module to authenticate users and control door access.
- **Automatic Light and door Control:** Lights turn on/off based on the number of people detected in the room.
- **Beeping Alert:** Alerts during door operations for additional feedback.

## Components Used

- Arduino Uno (or any compatible microcontroller)
- RC522 RFID Module
- Servo Motor (for door automation)
- LEDs (for light control)
- Piezo Buzzer (for door operation alert)
- Resistors, Wires, and Breadboard


## Circuit Diagram

Make sure to connect the components as per the following table:

| Component       | Pin Connection |
|------------------|----------------|
| RFID SDA        | Pin 10         |
| RFID SCK        | Pin 13         |
| RFID MOSI       | Pin 11         |
| RFID MISO       | Pin 12         |
| RFID RST        | Pin 9          |
| Input Button    | Pin 6          |
| Output Button   | Pin 7          |
| Light (LED)     | Pin 3          |
| Door Servo      | Pin 1          |
| Buzzer          | Pin 5          |

## Usage

- Scan a valid RFID card to open the door.
- The light will turn on if there is at least one person in the room.

