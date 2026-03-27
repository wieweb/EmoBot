#include "face_sad.h"

#include "colors.h"
#include "face_common.h"
#include "face_state.h"

namespace {

void drawSadEye(int x, int y, bool isLeft, uint8_t blinkLevel) {
  if (blinkLevel == 0) {
    if (isLeft) {
      FaceCommon::drawQuadraticCurve(x - 18, y - 12, x - 2, y - 30, x + 16, y - 2, Colors::Cyan, 6);
    } else {
      FaceCommon::drawQuadraticCurve(x - 16, y - 2, x + 2, y - 30, x + 18, y - 12, Colors::Cyan, 6);
    }
    return;
  }

  if (blinkLevel == 1) {
    if (isLeft) {
      FaceCommon::drawQuadraticCurve(x - 16, y - 4, x - 2, y - 14, x + 14, y + 6, Colors::Cyan, 5);
    } else {
      FaceCommon::drawQuadraticCurve(x - 14, y + 6, x + 2, y - 14, x + 16, y - 4, Colors::Cyan, 5);
    }
    return;
  }

  FaceCommon::drawEyeBar(x, y + 10, 44, 8, Colors::Cyan);
}

}  // namespace

namespace FaceSad {

void drawEyes() {
  const FaceState::RenderState& state = FaceState::current();
  const int leftX = FaceCommon::kLeftEyeX + state.eyeOffsetX + state.eyeInsetX;
  const int rightX = FaceCommon::kRightEyeX + state.eyeOffsetX - state.eyeInsetX;
  const int eyeY = FaceCommon::kEyeY + state.eyeOffsetY;

  drawSadEye(leftX, eyeY, true, state.leftBlinkLevel);
  drawSadEye(rightX, eyeY, false, state.rightBlinkLevel);
}

void drawMouth() {
  const FaceState::RenderState& state = FaceState::current();
  const int width = max(52, 84 + state.mouthWidthDelta);
  const int height = max(18, 36 + state.mouthHeightDelta);
  const int mouthY = FaceCommon::kMouthY + 10 + state.mouthOffsetY;

  FaceCommon::drawFrown(FaceCommon::kMouthCenterX, mouthY, width, height, Colors::Cyan, 6);
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

}  // namespace FaceSad
