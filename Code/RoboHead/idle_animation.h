#pragma once

#include <Arduino.h>

namespace IdleAnimation {

void begin(unsigned long now);
void update(unsigned long now);
void notifyInteraction(unsigned long now);

}  // namespace IdleAnimation
