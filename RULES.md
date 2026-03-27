# EmoBot Rules

This file captures the long-lived project context so future work stays consistent.

## Project Goal

`EmoBot` is a small personal robot for Tobias.
The project should grow step by step from an expressive animated head into a friendly interactive robot.

The robot is not meant to be a generic tech demo.
Personality, readability, and maintainability matter more than feature count.

## Core Direction

- The robot should feel friendly, calm, and child-appropriate.
- The display face is a primary communication channel, not a decorative extra.
- Hardware, firmware, and higher-level behavior should stay modular.
- Long-term structure is more important than quick hacks.

## System Architecture

The project is designed around two controllers:

1. `Brain`
   High-level behavior, sensors, decisions, and future AI integration.
2. `Head Controller`
   Display rendering, face animation, servos, and time-critical hardware control.

Communication between both controllers should happen over `UART`.

## Hardware Assumptions

- Main controller: `ESP32-S3 DevKitC-1`
- Head controller: `ESP32-S3 Super Mini` or another compact `ESP32-S3` board
- Display: `1.69" ST7789`, physical panel `240x280`, used in firmware as a rotated `280x240` screen
- Servos must use an external `5V` supply and must never be powered directly from GPIO pins
- All components must share a common `GND`

## Current Focus

The current work is focused on the head module:

- Render expressive faces on the LCD
- Build non-blocking idle animations
- Start with subtle eye behavior such as blinking
- Prepare for future servo control and command handling

## Code Rules

- Keep the codebase modular.
- Code and documentation language should be English.
- `RoboHead.ino` should contain only high-level setup and loop orchestration.
- Display-specific logic belongs in `display.*`.
- Shared face drawing primitives belong in `face_common.*`.
- Each face or emotion belongs in its own module such as `face_happy.*`, `face_angry.*`, or `face_worried.*`.
- Gallery and animation coordination belong in dedicated modules such as `face_gallery.*` and `idle_animation.*`.
- Hardware constants belong in central headers such as `pins.h`, `colors.h`, and similar config files.
- Do not duplicate pin values, colors, or timing constants across multiple files without a reason.
- New features should extend the existing structure instead of collapsing logic back into one large file.

## Face and Animation Rules

- Expressions should be emotionally clear, technically simple, and easy to read at a glance.
- Motion should feel calm and deliberate, not hyperactive.
- Idle behavior should make the robot feel alive without becoming distracting.
- Avoid full-screen redraws for small face changes when a local redraw is sufficient.
- Use non-blocking timing based on `millis()` for animations and state changes.
- Preserve facial readability during animation; blinking should not disturb the mouth or other unaffected regions.

## Development Rules

- Prefer small, clearly separated iterations.
- Do not silently change core hardware assumptions.
- When adding pins, displays, servos, or timing-critical behavior, update central configuration files first.
- When adding a new face mode, first decide whether it deserves its own module instead of becoming a special case in another file.
- Avoid `delay()` for animation timing or controller flow unless there is a very explicit reason.

## Long-Term Growth Path

The project should evolve roughly in this order:

1. Stable LCD face with expressive animations
2. Head movement with servos
3. Command communication between Brain and Head Controller
4. Sensors such as camera and microphones
5. Interactive behavior and later AI-driven features

## Always Keep In Mind

- This is Tobias's personal robot.
- Friendly character and maintainability are more important than technical complexity for its own sake.
- New architecture should build on the current modular structure, not fight it.
