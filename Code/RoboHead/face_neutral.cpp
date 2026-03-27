#include "face_neutral.h"

#include "colors.h"
#include "face_common.h"
#include "face_state.h"

namespace FaceNeutral {

void drawEyes() {
  const FaceState::RenderState& state = FaceState::current();
  const int leftX = FaceCommon::kLeftEyeX + state.eyeOffsetX + state.eyeInsetX;
  const int rightX = FaceCommon::kRightEyeX + state.eyeOffsetX - state.eyeInsetX;
  const int eyeY = FaceCommon::kEyeY + state.eyeOffsetY;

  FaceCommon::drawBlinkablePillEye(leftX, eyeY, 14, Colors::Cyan, state.leftBlinkLevel);
  FaceCommon::drawBlinkablePillEye(rightX, eyeY, 14, Colors::Cyan, state.rightBlinkLevel);
}

void drawMouth() {
}

void draw() {
  FaceCommon::clearCanvas();
  drawEyes();
}

void drawBlink() {
  FaceCommon::clearEyeArea();
  drawEyes();
}

}  // namespace FaceNeutral
