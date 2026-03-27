#include "face_neutral.h"

#include "colors.h"
#include "face_common.h"

namespace FaceNeutral {

void drawEyes() {
  FaceCommon::drawDotEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 14, Colors::Cyan);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 14, Colors::Cyan);
}

void draw() {
  FaceCommon::clearCanvas();
  drawEyes();
}

void drawBlink() {
  FaceCommon::clearEyeArea();
  FaceCommon::drawClosedEyes(Colors::Cyan, 48, 8);
}

}  // namespace FaceNeutral
