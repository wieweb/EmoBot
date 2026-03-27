#include "face_sad.h"

#include "colors.h"
#include "face_common.h"

namespace FaceSad {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawQuadraticCurve(FaceCommon::kLeftEyeX - 10, FaceCommon::kEyeY - 8, FaceCommon::kLeftEyeX - 2, FaceCommon::kEyeY - 18, FaceCommon::kLeftEyeX + 8, FaceCommon::kEyeY - 2, Colors::Cyan, 4);
  FaceCommon::drawQuadraticCurve(FaceCommon::kRightEyeX - 8, FaceCommon::kEyeY - 2, FaceCommon::kRightEyeX + 2, FaceCommon::kEyeY - 18, FaceCommon::kRightEyeX + 10, FaceCommon::kEyeY - 8, Colors::Cyan, 4);
  FaceCommon::drawFrown(FaceCommon::kMouthCenterX, FaceCommon::kMouthY + 6, 40, 18, Colors::Cyan, 4);
}

}  // namespace FaceSad
