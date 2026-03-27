#include "face_laugh.h"

#include "colors.h"
#include "face_common.h"

namespace FaceLaugh {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawQuadraticCurve(FaceCommon::kLeftEyeX - 22, FaceCommon::kEyeY + 6, FaceCommon::kLeftEyeX, FaceCommon::kEyeY - 20, FaceCommon::kLeftEyeX + 22, FaceCommon::kEyeY + 6, Colors::Cyan, 6);
  FaceCommon::drawQuadraticCurve(FaceCommon::kRightEyeX - 22, FaceCommon::kEyeY + 6, FaceCommon::kRightEyeX, FaceCommon::kEyeY - 20, FaceCommon::kRightEyeX + 22, FaceCommon::kEyeY + 6, Colors::Cyan, 6);
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 92, 38, Colors::Cyan, 6);
}

}  // namespace FaceLaugh
