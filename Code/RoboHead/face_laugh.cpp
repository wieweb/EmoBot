#include "face_laugh.h"

#include "colors.h"
#include "face_common.h"

namespace FaceLaugh {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawQuadraticCurve(FaceCommon::kLeftEyeX - 12, FaceCommon::kEyeY + 2, FaceCommon::kLeftEyeX, FaceCommon::kEyeY - 12, FaceCommon::kLeftEyeX + 12, FaceCommon::kEyeY + 2, Colors::Cyan, 4);
  FaceCommon::drawQuadraticCurve(FaceCommon::kRightEyeX - 12, FaceCommon::kEyeY + 2, FaceCommon::kRightEyeX, FaceCommon::kEyeY - 12, FaceCommon::kRightEyeX + 12, FaceCommon::kEyeY + 2, Colors::Cyan, 4);
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 44, 18, Colors::Cyan, 4);
}

}  // namespace FaceLaugh
