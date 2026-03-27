#include "face_surprised.h"

#include "colors.h"
#include "face_common.h"
#include "face_state.h"

namespace FaceSurprised {

void drawEyes() {
  const FaceState::RenderState& state = FaceState::current();
  const int leftX = FaceCommon::kLeftEyeX + state.eyeOffsetX + state.eyeInsetX;
  const int rightX = FaceCommon::kRightEyeX + state.eyeOffsetX - state.eyeInsetX;
  const int eyeY = FaceCommon::kEyeY + state.eyeOffsetY - 2;

  FaceCommon::drawBlinkablePillEye(leftX, eyeY, 15, Colors::Cyan, state.leftBlinkLevel);
  FaceCommon::drawBlinkablePillEye(rightX, eyeY, 15, Colors::Cyan, state.rightBlinkLevel);
}

void drawMouth() {
  const FaceState::RenderState& state = FaceState::current();
  const int radius = max(10, 22 + state.mouthRadiusDelta);
  const int mouthY = FaceCommon::kMouthY + 2 + state.mouthOffsetY;

  FaceCommon::drawOpenMouth(FaceCommon::kMouthCenterX, mouthY, radius, Colors::Cyan);
}

void draw() {
  FaceCommon::clearCanvas();
  drawEyes();
  drawMouth();
}

void drawBlink() {
  FaceCommon::clearEyeArea();
  drawEyes();
}

}  // namespace FaceSurprised
