#pragma once

#include <Arduino.h>

namespace CommandInterface {

/// Initialize the serial command interface state.
void begin();
/// Consume serial input and execute complete commands without blocking.
void update(unsigned long now);

}  // namespace CommandInterface
