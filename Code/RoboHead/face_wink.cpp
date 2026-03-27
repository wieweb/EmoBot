#include "face_wink.h"

#include "colors.h"
#include "face_common.h"

namespace FaceWink {

namespace {
void drawMouth() {
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 80, 34, Colors::Cyan, 6);
}
}  // namespace

void drawEyes() {
  FaceCommon::drawThickLine(FaceCommon::kLeftEyeX - 24, FaceCommon::kEyeY, FaceCommon::kLeftEyeX + 22, FaceCommon::kEyeY, Colors::Cyan, 6);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY - 2, 14, Colors::Cyan);
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

}  // namespace FaceWink
