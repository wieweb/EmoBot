#include "face_happy.h"

#include "colors.h"
#include "face_common.h"

namespace FaceHappy {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawDotEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 8, Colors::Cyan);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 8, Colors::Cyan);
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 42, 20, Colors::Cyan, 4);
}

}  // namespace FaceHappy
