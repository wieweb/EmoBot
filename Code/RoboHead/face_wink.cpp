#include "face_wink.h"

#include "colors.h"
#include "face_common.h"

namespace FaceWink {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawThickLine(FaceCommon::kLeftEyeX - 12, FaceCommon::kEyeY, FaceCommon::kLeftEyeX + 10, FaceCommon::kEyeY, Colors::Cyan, 4);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY - 2, 8, Colors::Cyan);
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 34, 16, Colors::Cyan, 4);
}

}  // namespace FaceWink
