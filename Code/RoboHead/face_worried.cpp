#include "face_worried.h"

#include "colors.h"
#include "face_common.h"
#include "face_state.h"

namespace FaceWorried {

void drawEyes() {
  const FaceState::RenderState& state = FaceState::current();
  const int leftX = FaceCommon::kLeftEyeX + state.eyeOffsetX + state.eyeInsetX;
  const int rightX = FaceCommon::kRightEyeX + state.eyeOffsetX - state.eyeInsetX;
  const int eyeY = FaceCommon::kEyeY + state.eyeOffsetY;

  FaceCommon::drawBlinkablePillEye(leftX, eyeY, 13, Colors::Cyan, state.leftBlinkLevel);
  FaceCommon::drawBlinkablePillEye(rightX, eyeY, 13, Colors::Cyan, state.rightBlinkLevel);
  FaceCommon::drawQuadraticCurve(leftX - 20, eyeY - 20, leftX - 2, eyeY - 34, leftX + 16, eyeY - 10, Colors::Cyan, 5);
  FaceCommon::drawQuadraticCurve(rightX - 16, eyeY - 10, rightX + 2, eyeY - 34, rightX + 20, eyeY - 20, Colors::Cyan, 5);
}

void drawMouth() {
  const FaceState::RenderState& state = FaceState::current();
  const int width = max(36, 60 + state.mouthWidthDelta);
  const int height = max(12, 26 + state.mouthHeightDelta);
  const int mouthY = FaceCommon::kMouthY + 4 + state.mouthOffsetY;

  FaceCommon::drawFrown(FaceCommon::kMouthCenterX, mouthY, width, height, Colors::Cyan, 5);
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

}  // namespace FaceWorried
