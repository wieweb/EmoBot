#include "face_angry.h"

#include "colors.h"
#include "face_common.h"

namespace FaceAngry {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawThickLine(FaceCommon::kLeftEyeX - 12, FaceCommon::kEyeY - 10, FaceCommon::kLeftEyeX + 10, FaceCommon::kEyeY - 2, Colors::Pink, 6);
  FaceCommon::drawThickLine(FaceCommon::kRightEyeX - 10, FaceCommon::kEyeY - 2, FaceCommon::kRightEyeX + 12, FaceCommon::kEyeY - 10, Colors::Pink, 6);
  FaceCommon::drawFrown(FaceCommon::kMouthCenterX, FaceCommon::kMouthY + 10, 44, 22, Colors::Pink, 4);
}

}  // namespace FaceAngry
