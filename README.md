# MyBluetoothCar

This repository contains the code for controlling an ESP32-based robotic car using the Dabble mobile application via Bluetooth. The car has functionalities for motor control and servo-based steering.

## Pictures 

You can find 5 views phots and an mp4 vid to show you what the result looks like (take it as a reference) in the pictures folder in this repo.

## Features

- Control the car's movement (forward, backward) using the Dabble Gamepad module.

- Adjust the servo motor to steer the car left, right, or center.

- Smooth motor speed control using PWM.

## Hardware Requirements

- Car chasis (i used lego)

- ESP32 board (i used ESP32 WROOM 32U with external antenna).

- Motor driver module (i used l298n).

- 1 DC motor (or more if you like but make sure to adjust the code).

- Servo motor (for steering).

- Battery pack (i used 4 AA battery pack).

- Switch button (used to set the car ON/OFF).

- Mini Bread Board.

- Bluetooth-enabled smartphone with the Dabble app.

## Software Requirements

- PlatformIO IDE

- ESP32 Board support in PlatformIO

- DabbleESP32 library

- ESP32Servo library

## Pin Configuration

| Component          | Pin on ESP32 |
| ------------------ | ------------ |
| Enable Right Motor | GPIO 23      |
| Right Motor Pin 1  | GPIO 18      |
| Right Motor Pin 2  | GPIO 19      |
| Servo Motor        | GPIO 13      |

## Code Explanation

### Dependencies

```cpp
#include <Arduino.h>
#include <ESP32Servo.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
```

- `ESP32Servo.h`: Library to control servo motors.

- `DabbleESP32.h`: Library to use the Dabble app for Bluetooth communication.

### Motor Control

- The motor's speed and direction are controlled using PWM and two control pins (`RightMotorPin1`, `RightMotorPin2`).

- The `rotateMotor()` function adjusts the motor speed and direction.

### Servo Control

- The servo motor is used for steering and controlled via the `myServo` object.

- The servo position is set based on the Dabble Gamepad inputs (left, right, center).

### Dabble Integration

- The `Dabble.begin("MyBluetoothCar")` initializes Bluetooth communication.

- Gamepad inputs from the Dabble app are processed to control the car's movement and steering.

### Main Functionalities

- Move forward: Press **Up** on the Gamepad.

- Move backward: Press **Down** on the Gamepad.

- Steer left: Press **Left** on the Gamepad.

- Steer right: Press **Right** on the Gamepad.

- Reset steering to center: Press **Circle** on the Gamepad.

## Installation

1. Clone this repository:
   
   ```
   git clone https://github.com/yourusername/MyBluetoothCar.git
   ```

2. Open the code in PlatformIO IDE.

3. Install the required libraries:
   
   - ESP32Servo
   
   - DabbleESP32

4. Build and upload the code to the ESP32 board using PlatformIO.

## Usage

1. Power up the car.

2. Open the Dabble app on your smartphone.

3. Connect to the ESP32 via Bluetooth ("MyBluetoothCar").

4. Use the Gamepad module in the Dabble app to control the car.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgements

- [ESP32Servo Library](https://github.com/madhephaestus/ESP32Servo)

- [DabbleESP32 Library](https://github.com/STEMpedia/Dabble-ESP32)

- [Dabble App](https://thestempedia.com/product/dabble/)

---

Feel free to contribute to this project by submitting issues or pull requests!


