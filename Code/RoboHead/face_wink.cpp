#include "face_wink.h"

#include "colors.h"
#include "face_common.h"

namespace FaceWink {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawThickLine(FaceCommon::kLeftEyeX - 24, FaceCommon::kEyeY, FaceCommon::kLeftEyeX + 22, FaceCommon::kEyeY, Colors::Cyan, 6);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY - 2, 14, Colors::Cyan);
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 80, 34, Colors::Cyan, 6);
}

}  // namespace FaceWink
