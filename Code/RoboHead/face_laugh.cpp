#include "face_laugh.h"

#include "colors.h"
#include "face_common.h"
#include "face_state.h"

namespace {

void drawLaughEye(int x, int y, uint8_t blinkLevel) {
  if (blinkLevel == 0) {
    FaceCommon::drawQuadraticCurve(x - 22, y + 6, x, y - 20, x + 22, y + 6, Colors::Cyan, 6);
    return;
  }

  if (blinkLevel == 1) {
    FaceCommon::drawQuadraticCurve(x - 18, y + 10, x, y - 4, x + 18, y + 10, Colors::Cyan, 5);
    return;
  }

  FaceCommon::drawEyeBar(x, y + 12, 50, 8, Colors::Cyan);
}

}  // namespace

namespace FaceLaugh {

void drawEyes() {
  const FaceState::RenderState& state = FaceState::current();
  const int leftX = FaceCommon::kLeftEyeX + state.eyeOffsetX + state.eyeInsetX;
  const int rightX = FaceCommon::kRightEyeX + state.eyeOffsetX - state.eyeInsetX;
  const int eyeY = FaceCommon::kEyeY + state.eyeOffsetY;

  drawLaughEye(leftX, eyeY, state.leftBlinkLevel);
  drawLaughEye(rightX, eyeY, state.rightBlinkLevel);
}

void drawMouth() {
  const FaceState::RenderState& state = FaceState::current();
  const int width = max(60, 92 + state.mouthWidthDelta);
  const int height = max(18, 38 + state.mouthHeightDelta);
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

}  // namespace FaceLaugh
