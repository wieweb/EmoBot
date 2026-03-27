#include "face_happy.h"

#include "colors.h"
#include "face_common.h"

namespace FaceHappy {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawDotEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 14, Colors::Cyan);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 14, Colors::Cyan);
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 86, 38, Colors::Cyan, 6);
}

}  // namespace FaceHappy
