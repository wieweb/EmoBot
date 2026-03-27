#include "face_angry.h"

#include "colors.h"
#include "face_common.h"
#include "face_state.h"

namespace {

void drawAngryEye(int x, int y, bool isLeft, uint8_t blinkLevel) {
  if (blinkLevel == 0) {
    if (isLeft) {
      FaceCommon::drawThickLine(x - 24, y - 14, x + 22, y - 1, Colors::Pink, 8);
    } else {
      FaceCommon::drawThickLine(x - 22, y - 1, x + 24, y - 14, Colors::Pink, 8);
    }
    return;
  }

  if (blinkLevel == 1) {
    if (isLeft) {
      FaceCommon::drawThickLine(x - 24, y - 7, x + 22, y + 3, Colors::Pink, 7);
    } else {
      FaceCommon::drawThickLine(x - 22, y + 3, x + 24, y - 7, Colors::Pink, 7);
    }
    return;
  }

  if (isLeft) {
    FaceCommon::drawThickLine(x - 22, y + 6, x + 20, y + 10, Colors::Pink, 6);
  } else {
    FaceCommon::drawThickLine(x - 20, y + 10, x + 22, y + 6, Colors::Pink, 6);
  }
}

}  // namespace

namespace FaceAngry {

void drawEyes() {
  const FaceState::RenderState& state = FaceState::current();
  const int leftX = FaceCommon::kLeftEyeX + state.eyeOffsetX + state.eyeInsetX;
  const int rightX = FaceCommon::kRightEyeX + state.eyeOffsetX - state.eyeInsetX;
  const int eyeY = FaceCommon::kEyeY + state.eyeOffsetY;

  drawAngryEye(leftX, eyeY, true, state.leftBlinkLevel);
  drawAngryEye(rightX, eyeY, false, state.rightBlinkLevel);
}

void drawMouth() {
  const FaceState::RenderState& state = FaceState::current();
  const int width = max(58, 92 + state.mouthWidthDelta);
  const int height = max(20, 42 + state.mouthHeightDelta);
  const int mouthY = FaceCommon::kMouthY + 10 + state.mouthOffsetY;

  FaceCommon::drawFrown(FaceCommon::kMouthCenterX, mouthY, width, height, Colors::Pink, 6);
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

}  // namespace FaceAngry
