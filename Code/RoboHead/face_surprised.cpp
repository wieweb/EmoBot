#include "face_surprised.h"

#include "colors.h"
#include "face_common.h"

namespace FaceSurprised {

namespace {
void drawMouth() {
  FaceCommon::drawOpenMouth(FaceCommon::kMouthCenterX, FaceCommon::kMouthY + 2, 22, Colors::Cyan);
}
}  // namespace

void drawEyes() {
  FaceCommon::drawDotEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY - 2, 15, Colors::Cyan);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY - 2, 15, Colors::Cyan);
}

void draw() {
  FaceCommon::clearCanvas();
  drawEyes();
  drawMouth();
}

void drawBlink() {
  FaceCommon::clearEyeArea();
  FaceCommon::drawClosedEyes(Colors::Cyan, 50, 8);
}

}  // namespace FaceSurprised
