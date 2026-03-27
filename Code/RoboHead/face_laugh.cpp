#include "face_laugh.h"

#include "colors.h"
#include "face_common.h"

namespace FaceLaugh {

namespace {
void drawMouth() {
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 92, 38, Colors::Cyan, 6);
}
}  // namespace

void drawEyes() {
  FaceCommon::drawQuadraticCurve(FaceCommon::kLeftEyeX - 22, FaceCommon::kEyeY + 6, FaceCommon::kLeftEyeX, FaceCommon::kEyeY - 20, FaceCommon::kLeftEyeX + 22, FaceCommon::kEyeY + 6, Colors::Cyan, 6);
  FaceCommon::drawQuadraticCurve(FaceCommon::kRightEyeX - 22, FaceCommon::kEyeY + 6, FaceCommon::kRightEyeX, FaceCommon::kEyeY - 20, FaceCommon::kRightEyeX + 22, FaceCommon::kEyeY + 6, Colors::Cyan, 6);
}

void draw() {
  FaceCommon::clearCanvas();
  drawEyes();
  drawMouth();
}

void drawBlink() {
  FaceCommon::clearEyeArea();
  FaceCommon::drawClosedEyes(Colors::Cyan, 52, 8);
}

}  // namespace FaceLaugh
