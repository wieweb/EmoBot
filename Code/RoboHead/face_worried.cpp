#include "face_worried.h"

#include "colors.h"
#include "face_common.h"

namespace FaceWorried {

namespace {
void drawMouth() {
  FaceCommon::drawFrown(FaceCommon::kMouthCenterX, FaceCommon::kMouthY + 4, 60, 26, Colors::Cyan, 5);
}
}  // namespace

void drawEyes() {
  FaceCommon::drawDotEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 13, Colors::Cyan);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 13, Colors::Cyan);
  FaceCommon::drawQuadraticCurve(FaceCommon::kLeftEyeX - 20, FaceCommon::kEyeY - 20, FaceCommon::kLeftEyeX - 2, FaceCommon::kEyeY - 34, FaceCommon::kLeftEyeX + 16, FaceCommon::kEyeY - 10, Colors::Cyan, 5);
  FaceCommon::drawQuadraticCurve(FaceCommon::kRightEyeX - 16, FaceCommon::kEyeY - 10, FaceCommon::kRightEyeX + 2, FaceCommon::kEyeY - 34, FaceCommon::kRightEyeX + 20, FaceCommon::kEyeY - 20, Colors::Cyan, 5);
}

void draw() {
  FaceCommon::clearCanvas();
  drawEyes();
  drawMouth();
}

void drawBlink() {
  FaceCommon::clearEyeArea();
  FaceCommon::drawClosedEyes(Colors::Cyan, 46, 8);
  FaceCommon::drawQuadraticCurve(FaceCommon::kLeftEyeX - 20, FaceCommon::kEyeY - 20, FaceCommon::kLeftEyeX - 2, FaceCommon::kEyeY - 34, FaceCommon::kLeftEyeX + 16, FaceCommon::kEyeY - 10, Colors::Cyan, 5);
  FaceCommon::drawQuadraticCurve(FaceCommon::kRightEyeX - 16, FaceCommon::kEyeY - 10, FaceCommon::kRightEyeX + 2, FaceCommon::kEyeY - 34, FaceCommon::kRightEyeX + 20, FaceCommon::kEyeY - 20, Colors::Cyan, 5);
}

}  // namespace FaceWorried
