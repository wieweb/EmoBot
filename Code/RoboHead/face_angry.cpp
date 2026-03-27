#include "face_angry.h"

#include "colors.h"
#include "face_common.h"

namespace FaceAngry {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawThickLine(FaceCommon::kLeftEyeX - 24, FaceCommon::kEyeY - 14, FaceCommon::kLeftEyeX + 22, FaceCommon::kEyeY - 1, Colors::Pink, 8);
  FaceCommon::drawThickLine(FaceCommon::kRightEyeX - 22, FaceCommon::kEyeY - 1, FaceCommon::kRightEyeX + 24, FaceCommon::kEyeY - 14, Colors::Pink, 8);
  FaceCommon::drawFrown(FaceCommon::kMouthCenterX, FaceCommon::kMouthY + 10, 92, 42, Colors::Pink, 6);
}

}  // namespace FaceAngry
