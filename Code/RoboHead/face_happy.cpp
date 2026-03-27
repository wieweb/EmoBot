#include "face_happy.h"

#include "colors.h"
#include "face_common.h"
#include "face_state.h"

namespace FaceHappy {

void drawEyes() {
  const FaceState::RenderState& state = FaceState::current();
  const int leftX = FaceCommon::kLeftEyeX + state.eyeOffsetX + state.eyeInsetX;
  const int rightX = FaceCommon::kRightEyeX + state.eyeOffsetX - state.eyeInsetX;
  const int eyeY = FaceCommon::kEyeY + state.eyeOffsetY;

  FaceCommon::drawBlinkablePillEye(leftX, eyeY, 14, Colors::Cyan, state.leftBlinkLevel);
  FaceCommon::drawBlinkablePillEye(rightX, eyeY, 14, Colors::Cyan, state.rightBlinkLevel);
}

void drawMouth() {
  const FaceState::RenderState& state = FaceState::current();
  const int width = max(58, 86 + state.mouthWidthDelta);
  const int height = max(20, 38 + state.mouthHeightDelta);
  const int mouthY = FaceCommon::kMouthY + state.mouthOffsetY;

  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, mouthY, width, height, Colors::Cyan, 6);
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

}  // namespace FaceHappy
