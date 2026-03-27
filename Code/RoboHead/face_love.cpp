#include "face_love.h"

#include "colors.h"
#include "face_common.h"

namespace FaceLove {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawHeartEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 38, Colors::Pink);
  FaceCommon::drawHeartEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 38, Colors::Pink);
  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 78, 30, Colors::Pink, 6);
}

}  // namespace FaceLove
