#include "buttons.h"

#include "pins.h"

namespace {

constexpr unsigned long DEBOUNCE_MS = 30;
constexpr unsigned long LONG_PRESS_MS = 550;

bool lastReading = HIGH;
bool stableState = HIGH;
bool nextPressed = false;
bool previousPressed = false;

unsigned long lastChangeTime = 0;
unsigned long pressedSince = 0;

}  // namespace

namespace Buttons {

void begin() {
  pinMode(BUTTON_FACE, INPUT_PULLUP);
}

void update(unsigned long now) {
  const bool reading = digitalRead(BUTTON_FACE);

  if (reading != lastReading) {
    lastChangeTime = now;
    lastReading = reading;
  }

  if ((now - lastChangeTime) < DEBOUNCE_MS) {
    return;
  }

  if (reading == stableState) {
    return;
  }

  stableState = reading;

  if (stableState == LOW) {
    pressedSince = now;
    return;
  }

  const unsigned long pressDuration = now - pressedSince;
  if (pressDuration >= LONG_PRESS_MS) {
    previousPressed = true;
  } else {
    nextPressed = true;
  }
}

bool consumeNextPressed() {
  const bool wasPressed = nextPressed;
  nextPressed = false;
  return wasPressed;
}

bool consumePreviousPressed() {
  const bool wasPressed = previousPressed;
  previousPressed = false;
  return wasPressed;
}

}  // namespace Buttons
