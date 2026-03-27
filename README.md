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
- faster saccade-style eye jumps layered on top of normal gaze drift
- short attention reactions after local interaction or external commands
- narrower eye spacing and a slightly narrower mouth during stronger side looks
- mood-driven idle behavior with calm, curious, sleepy, and cheerful variations
- small mouth motion and micro-expression changes during idle
- a fullscreen single framebuffer in PSRAM
- partial eye and mouth region clears inside the framebuffer before local redraws
- full-frame LCD presentation from the completed framebuffer to eliminate visible flicker

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

The current rendering path uses a single fullscreen framebuffer:

- draw operations render into an offscreen `280x240` RGB565 buffer
- the finished frame is pushed to the ST7789 in one full-screen transfer
- local helpers such as eye and mouth clears are still used inside the buffer so old pixels do not remain when only part of the face changes

## Firmware Structure

The current `Code/RoboHead` structure is intentionally modular:

- `RoboHead.ino`: setup and loop orchestration
- `display.*`: display initialization and access
- `buttons.*`: button input and press handling
- `command_interface.*`: serial command parsing for external control
- `face_common.*`: shared face drawing primitives
- `face_state.*`: shared render state for eye offsets, blink levels, and mouth adjustments
- `face_*.{h,cpp}`: individual face definitions
- `face_gallery.*`: face selection and dispatch
- `idle_animation.*`: non-blocking idle behavior such as blinking, gaze movement, and mood-based micro-animation

In practice, `display.*` now also owns the framebuffer and the final `present()` step that transfers the completed frame to the LCD.

## Serial Control

The current firmware also includes a first serial command interface so a second ESP32 can control the RoboHead over UART.

Supported command examples:

- `FACE happy`
- `FACE sad`
- `SHOW_FACE_HAPPY`
- `NEXT`
- `PREV`
- `INDEX 3`
- `BLINK`
- `ATTEND LEFT`
- `ATTEND RIGHT`
- `ATTEND CENTER`
- `PING`

The command interface currently focuses on face selection and simple animation triggers. It is meant as the first control layer between the future Brain controller and the head controller.

## Hardware Notes

- Servos must be powered from an external `5V` supply
- Servos must never be powered directly from ESP GPIO pins
- All modules must share common ground
- USB is mainly for programming and debugging

## Arduino Dependencies

To build `Code/RoboHead` in the Arduino IDE, install these libraries through the Library Manager:

- `Adafruit GFX Library`
- `Adafruit ST7735 and ST7789 Library`

The board package must also be installed:

- `esp32` by `Espressif Systems`

If `Adafruit_GFX.h` or `Adafruit_ST7789.h` is missing during compilation, the required library is not installed in the current Arduino environment yet.

## Development Guidelines

- Keep code and docs in English
- Prefer small, isolated modules
- Use non-blocking timing with `millis()` for animation behavior
- Build the face in the fullscreen framebuffer first, then present the completed frame to the LCD
- Keep local redraw helpers for eyes and mouth inside the framebuffer when only part of the expression changes
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
