#pragma once

#include <Arduino.h>

namespace Buttons {

void begin();
void update(unsigned long now);
bool consumeNextPressed();
bool consumePreviousPressed();

}  // namespace Buttons
