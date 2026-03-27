#include "face_happy.h"

#include "colors.h"
#include "face_common.h"

namespace FaceHappy {

namespace {
void drawMouth() {
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 86, 38, Colors::Cyan, 6);
}
}  // namespace

void drawEyes() {
  FaceCommon::drawDotEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 14, Colors::Cyan);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 14, Colors::Cyan);
}

void draw() {
  FaceCommon::clearCanvas();
  drawEyes();
  drawMouth();
}

void drawBlink() {
  FaceCommon::clearEyeArea();
  FaceCommon::drawClosedEyes(Colors::Cyan, 48, 8);
}

}  // namespace FaceHappy
