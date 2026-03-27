#include "buttons.h"
#include "display.h"
#include "face_gallery.h"
#include "idle_animation.h"

void setup() {
  Serial.begin(115200);

  Display::begin();
  Buttons::begin();
  FaceGallery::begin();
  IdleAnimation::begin(millis());
}

void loop() {
  const unsigned long now = millis();

  Buttons::update(now);

  if (Buttons::consumeNextPressed()) {
    FaceGallery::next();
  }

  if (Buttons::consumePreviousPressed()) {
    FaceGallery::previous();
  }

  FaceGallery::update(now);
}
