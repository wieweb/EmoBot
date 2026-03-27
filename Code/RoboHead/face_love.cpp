#include "face_love.h"

#include "colors.h"
#include "face_common.h"

namespace FaceLove {

namespace {
void drawMouth() {
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 78, 30, Colors::Pink, 6);
}
}  // namespace

void drawEyes() {
  FaceCommon::drawHeartEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 38, Colors::Pink);
  FaceCommon::drawHeartEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 38, Colors::Pink);
}

void draw() {
  FaceCommon::clearCanvas();
  drawEyes();
  drawMouth();
}

void drawBlink() {
  FaceCommon::clearEyeArea();
  FaceCommon::drawClosedEyes(Colors::Pink, 50, 8);
}

}  // namespace FaceLove
