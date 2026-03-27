#include "face_love.h"

#include "colors.h"
#include "face_common.h"
#include "face_state.h"

namespace {

void drawLoveEye(int x, int y, uint8_t blinkLevel) {
  if (blinkLevel == 0) {
    FaceCommon::drawHeartEye(x, y, 38, Colors::Pink);
    return;
  }

  if (blinkLevel == 1) {
    FaceCommon::drawEyeBar(x, y + 8, 48, 14, Colors::Pink);
    return;
  }

  FaceCommon::drawEyeBar(x, y + 12, 52, 8, Colors::Pink);
}

}  // namespace

namespace FaceLove {

void drawEyes() {
  const FaceState::RenderState& state = FaceState::current();
  const int leftX = FaceCommon::kLeftEyeX + state.eyeOffsetX + state.eyeInsetX;
  const int rightX = FaceCommon::kRightEyeX + state.eyeOffsetX - state.eyeInsetX;
  const int eyeY = FaceCommon::kEyeY + state.eyeOffsetY;

  drawLoveEye(leftX, eyeY, state.leftBlinkLevel);
  drawLoveEye(rightX, eyeY, state.rightBlinkLevel);
}

void drawMouth() {
  const FaceState::RenderState& state = FaceState::current();
  const int width = max(52, 78 + state.mouthWidthDelta);
  const int height = max(18, 30 + state.mouthHeightDelta);
  const int mouthY = FaceCommon::kMouthY + state.mouthOffsetY;

  FaceCommon::drawSmile(FaceCommon::kMouthCenterX, mouthY, width, height, Colors::Pink, 6);
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

}  // namespace FaceLove
