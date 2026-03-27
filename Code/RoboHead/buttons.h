#pragma once

#include <Arduino.h>

namespace Buttons {

/// Initialize button GPIOs and internal press state.
void begin();
/// Poll hardware and update debounced button state for this frame.
void update(unsigned long now);
/// Return and clear the queued "next face" button press.
bool consumeNextPressed();
/// Return and clear the queued "previous face" button press.
bool consumePreviousPressed();

}  // namespace Buttons
