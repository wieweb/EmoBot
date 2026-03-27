#pragma once

#include <Arduino.h>

namespace IdleAnimation {

/// Initialize idle timing and the shared animation state.
void begin(unsigned long now);
/// Advance non-blocking idle behavior and trigger redraws when needed.
void update(unsigned long now);
/// Inform the idle system about local interaction so it can reset timing.
void notifyInteraction(unsigned long now);
/// Trigger a short attention reaction toward left, center, or right.
void triggerAttention(unsigned long now, int8_t direction);
/// Trigger an immediate blink sequence.
void triggerBlink(unsigned long now);

}  // namespace IdleAnimation
