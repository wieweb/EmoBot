# EmoBot

## Overview

EmoBot is a small modular robot project centered around an expressive display-based head.
The project is being built step by step, starting with a friendly animated face and a clean split between low-level hardware control and higher-level behavior.

The current implementation focus is the `RoboHead` module:

- ST7789 display output
- reusable face drawing primitives
- multiple face expressions
- a non-blocking idle animation system

## Current Status

The head firmware already supports:

- multiple face modules such as happy, neutral, sad, angry, love, surprised, sleepy, laugh, wink, and worried
- a face gallery that can switch expressions
- larger face geometry that uses the display area more effectively
- vertical pill-shaped eyes for open-eye expressions
- idle blinking using randomized non-blocking timing
- multi-step blink variants including asymmetric and longer blinks
- subtle eye drift and occasional side glances
- narrower eye spacing and a slightly narrower mouth during stronger side looks
- mood-driven idle behavior with calm, curious, sleepy, and cheerful variations
- small mouth motion and micro-expression changes during idle
- partial redraws of the eye and mouth regions to reduce visible flicker

## Architecture

The overall robot is designed around two ESP32-based controllers with clearly separated responsibilities.

### Brain

- Board: `ESP32-S3 DevKitC-1`
- Location: robot body
- Responsibility: high-level logic, sensors, decisions, and later AI-related behavior

### Head Controller

- Board: `ESP32-S3 Super Mini` or a similar compact `ESP32-S3`
- Location: head / neck area
- Responsibility: display rendering, face animation, servo control, and time-critical hardware behavior

## Communication Model

The intended communication path between both controllers is `UART`.

The long-term idea is simple:

- the Brain sends compact commands
- the Head Controller executes those commands locally

Example command categories:

- `LOOK_LEFT`
- `LOOK_RIGHT`
- `TILT_UP`
- `SHOW_FACE_HAPPY`

## Display Notes

- Display type: `1.69" ST7789`
- Physical panel size: `240x280`
- Active firmware orientation: `280x240`
- Interface: `SPI`

The face renderer is built around a rotated landscape layout, so UI and animation decisions should follow the `280x240` coordinate space used by the firmware.

## Firmware Structure

The current `Code/RoboHead` structure is intentionally modular:

- `RoboHead.ino`: setup and loop orchestration
- `display.*`: display initialization and access
- `buttons.*`: button input and press handling
- `face_common.*`: shared face drawing primitives
- `face_state.*`: shared render state for eye offsets, blink levels, and mouth adjustments
- `face_*.{h,cpp}`: individual face definitions
- `face_gallery.*`: face selection and dispatch
- `idle_animation.*`: non-blocking idle behavior such as blinking, gaze movement, and mood-based micro-animation

## Hardware Notes

- Servos must be powered from an external `5V` supply
- Servos must never be powered directly from ESP GPIO pins
- All modules must share common ground
- USB is mainly for programming and debugging

## Development Guidelines

- Keep code and docs in English
- Prefer small, isolated modules
- Use non-blocking timing with `millis()` for animation behavior
- Avoid full-screen redraws for small visual updates when a local redraw is enough
- Keep expressive behavior centralized in shared state and idle coordination code instead of duplicating animation logic per face
- Extend the current structure instead of adding monolithic logic

## Roadmap

1. Stable and expressive LCD face
2. Head movement with servos
3. UART command handling between Brain and Head Controller
4. Sensor integration such as camera and microphones
5. More advanced interactive and AI-assisted behavior

## Repository Notes

- `RULES.md` contains the persistent project rules and design constraints
- `Documentations/partslist.md` contains the current core hardware list

EmoBot is intended to grow from a readable animated head into a friendly and technically clean personal robot.
