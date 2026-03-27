#include "idle_animation.h"

#include "face_common.h"
#include "face_gallery.h"

namespace {

constexpr unsigned long kBlinkClosedMs = 120;
constexpr unsigned long kBlinkIntervalMinMs = 2600;
constexpr unsigned long kBlinkIntervalMaxMs = 6200;

bool blinkActive = false;
unsigned long blinkEndsAt = 0;
unsigned long nextBlinkAt = 0;

unsigned long randomBlinkDelay() {
  return static_cast<unsigned long>(random(
    static_cast<long>(kBlinkIntervalMinMs),
    static_cast<long>(kBlinkIntervalMaxMs + 1)
  ));
}

void scheduleNextBlink(unsigned long now) {
  nextBlinkAt = now + randomBlinkDelay();
}

}  // namespace

namespace IdleAnimation {

void begin(unsigned long now) {
  randomSeed(static_cast<unsigned long>(micros()));
  blinkActive = false;
  blinkEndsAt = 0;
  scheduleNextBlink(now);
}

void update(unsigned long now) {
  if (blinkActive) {
    if (now < blinkEndsAt) {
      return;
    }

    blinkActive = false;
    FaceCommon::clearEyeArea();
    FaceGallery::drawEyesCurrent();
    scheduleNextBlink(now);
    return;
  }

  if (now < nextBlinkAt) {
    return;
  }

  blinkActive = true;
  blinkEndsAt = now + kBlinkClosedMs;
  FaceGallery::drawBlinkCurrent();
}

void notifyInteraction(unsigned long now) {
  blinkActive = false;
  blinkEndsAt = 0;
  scheduleNextBlink(now);
}

}  // namespace IdleAnimation
