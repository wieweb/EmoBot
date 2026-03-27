#include "face_wink.h"

#include "colors.h"
#include "face_common.h"
#include "face_state.h"

namespace {

void drawLeftEye(int x, int y, uint8_t blinkLevel) {
  if (blinkLevel == 0) {
    FaceCommon::drawThickLine(x - 24, y, x + 22, y, Colors::Cyan, 6);
    return;
  }

  if (blinkLevel == 1) {
    FaceCommon::drawThickLine(x - 20, y + 4, x + 18, y + 4, Colors::Cyan, 6);
    return;
  }

  FaceCommon::drawEyeBar(x, y + 10, 42, 8, Colors::Cyan);
}

}  // namespace

namespace FaceWink {

void drawEyes() {
  const FaceState::RenderState& state = FaceState::current();
  const int leftX = FaceCommon::kLeftEyeX + state.eyeOffsetX + state.eyeInsetX;
  const int rightX = FaceCommon::kRightEyeX + state.eyeOffsetX - state.eyeInsetX;
  const int eyeY = FaceCommon::kEyeY + state.eyeOffsetY;

  drawLeftEye(leftX, eyeY, state.leftBlinkLevel);
  FaceCommon::drawBlinkablePillEye(rightX, eyeY - 2, 14, Colors::Cyan, state.rightBlinkLevel);
}

void drawMouth() {
  const FaceState::RenderState& state = FaceState::current();
  const int width = max(56, 80 + state.mouthWidthDelta);
  const int height = max(18, 34 + state.mouthHeightDelta);
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

}  // namespace FaceWink
