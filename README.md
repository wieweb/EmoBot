# Roboter Project

## Overview
This project is a small, modular robot with a cute design inspired by consumer robots (similar to Cozmo). The focus is on a clean separation between hardware control and higher-level logic.

The robot currently consists of:
- A **compact movable head** with a display (face)
- A **static body** that contains the main controller ("brain")
- A **pan/tilt-ready architecture** for future extensions

---

## System Architecture

The system is built using **two ESP32 microcontrollers** with clearly separated responsibilities:

### 1. Brain (Main Controller)
- Board: **ESP32-S3 DevKitC-1**
- Location: Inside the robot body

#### Responsibilities:
- High-level logic and behavior
- Communication with sensors (future: camera, microphones)
- Decision making (e.g. where the robot should look)
- Sending commands to the head controller

---

### 2. Head Controller (Hardware Controller)
- Board: **ESP32-S3 Super Mini**
- Location: In or near the head/neck

#### Responsibilities:
- Driving the LCD display (robot face)
- Controlling servos (head movement)
- Executing low-level, real-time actions
- Receiving commands from the main controller

---

## Communication

The two controllers communicate via:
- **UART (serial communication)**

### Concept:
- The **Brain** sends simple commands
- The **Head Controller** executes them

#### Example commands:
- `LOOK_LEFT`
- `LOOK_RIGHT`
- `TILT_UP`
- `SHOW_FACE_HAPPY`

This keeps the system modular and scalable.

---

## Hardware Components

### Display (Face)
- 1.69" IPS LCD (240x280, SPI, ST7789)
- Connected to the **Head Controller**
- Used to render eyes, expressions, and animations

### Servo (Head Movement)
- MG90S Micro Servo (metal gear)
- Controlled by the **Head Controller**
- Powered directly from the 5V supply (not from ESP)

### Power Supply
- 5.1V / 5A USB-C power supply
- USB-C panel mount connector integrated into the body

#### Power Distribution:
- 5V → both ESP boards
- 5V → servo(s)
- Common GND across all components

---

## Mechanical Design

### Head
- Compact, rounded design
- LCD in the upper half (face)
- Camera planned below the display
- Microphone openings on left and right side
- Internal space for display and wiring

### Body
- Simple rectangular enclosure
- Contains:
  - Main ESP32-S3 (Brain)
  - Power input (USB-C panel mount)
- Designed for future mobility (wheels/tracks)

### Neck / Movement
- Initial version: **Tilt only (1 DOF)**
- Future: **Pan + Tilt (2 DOF)**

---

## Development Strategy

### Phase 1
- Static body
- Moving head (tilt)
- Display-based face
- Basic command communication

### Phase 2
- Add camera and microphones
- Implement basic tracking (face / direction)
- Add pan movement

### Phase 3
- Add mobile base (driving)
- Combine head movement with navigation

---

## Key Design Decisions

- Separation of concerns (Brain vs Hardware Controller)
- External power for servos (stability)
- Modular architecture for future upgrades
- Compact and clean mechanical design

---

## Future Extensions

- Face tracking using camera
- Sound localization using microphones
- Autonomous movement
- More expressive animations (eyes, emotions)
- Integration with AI systems

---

## Notes

- All grounds (GND) must be connected
- Servos must NOT be powered from ESP pins
- ESP boards are powered via 5V (VIN / 5V pin)
- USB is primarily used for programming/debugging

---

This project is designed to evolve step by step from a simple animated head into a fully interactive mobile robot.