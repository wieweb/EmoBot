#include "face_gallery.h"

#include "face_angry.h"
#include "face_happy.h"
#include "idle_animation.h"
#include "face_laugh.h"
#include "face_love.h"
#include "face_neutral.h"
#include "face_sad.h"
#include "face_sleepy.h"
#include "face_surprised.h"
#include "face_wink.h"
#include "face_worried.h"

namespace {

struct FaceEntry {
  const char* name;
  void (*draw)();
  void (*drawEyes)();
  void (*drawBlink)();
};

const FaceEntry FACES[] = {
  {"happy", FaceHappy::draw, FaceHappy::drawEyes, FaceHappy::drawBlink},
  {"wink", FaceWink::draw, FaceWink::drawEyes, FaceWink::drawBlink},
  {"sad", FaceSad::draw, FaceSad::drawEyes, FaceSad::drawBlink},
  {"angry", FaceAngry::draw, FaceAngry::drawEyes, FaceAngry::drawBlink},
  {"neutral", FaceNeutral::draw, FaceNeutral::drawEyes, FaceNeutral::drawBlink},
  {"love", FaceLove::draw, FaceLove::drawEyes, FaceLove::drawBlink},
  {"surprised", FaceSurprised::draw, FaceSurprised::drawEyes, FaceSurprised::drawBlink},
  {"sleepy", FaceSleepy::draw, FaceSleepy::drawEyes, FaceSleepy::drawBlink},
  {"laugh", FaceLaugh::draw, FaceLaugh::drawEyes, FaceLaugh::drawBlink},
  {"worried", FaceWorried::draw, FaceWorried::drawEyes, FaceWorried::drawBlink},
};

uint8_t currentFace = 0;

}  // namespace

namespace FaceGallery {

void begin() {
  drawCurrent();
}

void update(unsigned long now) {
  IdleAnimation::update(now);
}

void next() {
  currentFace = (currentFace + 1) % faceCount();
  drawCurrent();
  IdleAnimation::notifyInteraction(millis());
}

void previous() {
  currentFace = (currentFace == 0) ? (faceCount() - 1) : (currentFace - 1);
  drawCurrent();
  IdleAnimation::notifyInteraction(millis());
}

void drawCurrent() {
  FACES[currentFace].draw();
}

void drawEyesCurrent() {
  FACES[currentFace].drawEyes();
}

void drawBlinkCurrent() {
  FACES[currentFace].drawBlink();
}

const char* currentName() {
  return FACES[currentFace].name;
}

uint8_t currentIndex() {
  return currentFace;
}

uint8_t faceCount() {
  return static_cast<uint8_t>(sizeof(FACES) / sizeof(FACES[0]));
}

}  // namespace FaceGallery
