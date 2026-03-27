#include "face_love.h"

#include "colors.h"
#include "face_common.h"

namespace FaceLove {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawHeartEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY - 2, 24, Colors::Pink);
  FaceCommon::drawHeartEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY - 2, 24, Colors::Pink);
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 36, 14, Colors::Pink, 4);
}

}  // namespace FaceLove
