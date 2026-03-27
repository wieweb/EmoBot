#include "face_neutral.h"

#include "colors.h"
#include "face_common.h"

namespace FaceNeutral {

void draw() {
  FaceCommon::clearCanvas();
  FaceCommon::drawDotEye(FaceCommon::kLeftEyeX, FaceCommon::kEyeY, 8, Colors::Cyan);
  FaceCommon::drawDotEye(FaceCommon::kRightEyeX, FaceCommon::kEyeY, 8, Colors::Cyan);
}

}  // namespace FaceNeutral
