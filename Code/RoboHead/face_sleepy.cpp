#include "face_sleepy.h"

#include "colors.h"
#include "face_common.h"

namespace FaceSleepy {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawEyeBar(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 24, 4, Colors::Cyan);
  FaceCommon::drawEyeBar(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 24, 4, Colors::Cyan);
  FaceCommon::drawFlatMouth(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 28, Colors::Cyan, 3);
}

}  // namespace FaceSleepy
