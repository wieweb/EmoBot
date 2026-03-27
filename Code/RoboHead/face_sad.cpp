#include "face_sad.h"

#include "colors.h"
#include "face_common.h"

namespace FaceSad {

namespace {
void drawMouth() {
  FaceCommon::drawFrown(FaceCommon::kMouthCenterX, FaceCommon::kMouthY + 10, 84, 36, Colors::Cyan, 6);
}
}  // namespace

void drawEyes() {
  FaceCommon::drawQuadraticCurve(FaceCommon::kLeftEyeX - 18, FaceCommon::kEyeY - 12, FaceCommon::kLeftEyeX - 2, FaceCommon::kEyeY - 30, FaceCommon::kLeftEyeX + 16, FaceCommon::kEyeY - 2, Colors::Cyan, 6);
  FaceCommon::drawQuadraticCurve(FaceCommon::kRightEyeX - 16, FaceCommon::kEyeY - 2, FaceCommon::kRightEyeX + 2, FaceCommon::kEyeY - 30, FaceCommon::kRightEyeX + 18, FaceCommon::kEyeY - 12, Colors::Cyan, 6);
}

void draw() {
  FaceCommon::clearCanvas();
  drawEyes();
  drawMouth();
}

void drawBlink() {
  FaceCommon::clearEyeArea();
  FaceCommon::drawClosedEyes(Colors::Cyan, 46, 8);
}

}  // namespace FaceSad
