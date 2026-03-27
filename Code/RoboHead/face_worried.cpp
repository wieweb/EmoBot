#include "face_worried.h"

#include "colors.h"
#include "face_common.h"

namespace FaceWorried {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawDotEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 8, Colors::Cyan);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 8, Colors::Cyan);
  FaceCommon::drawQuadraticCurve(FaceCommon::kLeftEyeX - 12, FaceCommon::kEyeY - 16, FaceCommon::kLeftEyeX - 2, FaceCommon::kEyeY - 22, FaceCommon::kLeftEyeX + 8, FaceCommon::kEyeY - 8, Colors::Cyan, 3);
  FaceCommon::drawQuadraticCurve(FaceCommon::kRightEyeX - 8, FaceCommon::kEyeY - 8, FaceCommon::kRightEyeX + 2, FaceCommon::kEyeY - 22, FaceCommon::kRightEyeX + 12, FaceCommon::kEyeY - 16, Colors::Cyan, 3);
  FaceCommon::drawFrown(FaceCommon::kMouthCenterX, FaceCommon::kMouthY + 4, 28, 12, Colors::Cyan, 3);
}

}  // namespace FaceWorried
