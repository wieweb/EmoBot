#include "face_surprised.h"

#include "colors.h"
#include "face_common.h"

namespace FaceSurprised {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawDotEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY - 2, 15, Colors::Cyan);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY - 2, 15, Colors::Cyan);
  FaceCommon::drawOpenMouth(FaceCommon::kMouthCenterX, FaceCommon::kMouthY + 2, 22, Colors::Cyan);
}

}  // namespace FaceSurprised
