#include "face_gallery.h"

#include "face_angry.h"
#include "face_happy.h"
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
};

const FaceEntry FACES[] = {
  {"happy", FaceHappy::draw},
  {"wink", FaceWink::draw},
  {"sad", FaceSad::draw},
  {"angry", FaceAngry::draw},
  {"neutral", FaceNeutral::draw},
  {"love", FaceLove::draw},
  {"surprised", FaceSurprised::draw},
  {"sleepy", FaceSleepy::draw},
  {"laugh", FaceLaugh::draw},
  {"worried", FaceWorried::draw},
};

uint8_t currentFace = 0;

}  // namespace

namespace FaceGallery {

void begin() {
  drawCurrent();
}

void next() {
  currentFace = (currentFace + 1) % faceCount();
  drawCurrent();
}

void previous() {
  currentFace = (currentFace == 0) ? (faceCount() - 1) : (currentFace - 1);
  drawCurrent();
}

void drawCurrent() {
  FACES[currentFace].draw();
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
