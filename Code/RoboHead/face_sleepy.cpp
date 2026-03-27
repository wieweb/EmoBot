#include "face_sleepy.h"

#include "colors.h"
#include "face_common.h"

namespace FaceSleepy {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawEyeBar(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 48, 8, Colors::Cyan);
  FaceCommon::drawEyeBar(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 48, 8, Colors::Cyan);
  FaceCommon::drawFlatMouth(FaceCommon::kMouthCenterX, FaceCommon::kMouthY, 60, Colors::Cyan, 5);
}

}  // namespace FaceSleepy
