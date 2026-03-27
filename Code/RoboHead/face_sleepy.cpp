#include "face_sleepy.h"

#include "colors.h"
#include "face_common.h"
#include "face_state.h"

namespace FaceSleepy {

void drawEyes() {
  const FaceState::RenderState& state = FaceState::current();
  const int leftX = FaceCommon::kLeftEyeX + state.eyeOffsetX + state.eyeInsetX;
  const int rightX = FaceCommon::kRightEyeX + state.eyeOffsetX - state.eyeInsetX;
  const int eyeY = FaceCommon::kEyeY + state.eyeOffsetY;
  const int leftWidth = (state.leftBlinkLevel == 2) ? 42 : 48;
  const int rightWidth = (state.rightBlinkLevel == 2) ? 42 : 48;
  const int leftHeight = (state.leftBlinkLevel == 2) ? 6 : 8;
  const int rightHeight = (state.rightBlinkLevel == 2) ? 6 : 8;

  FaceCommon::drawEyeBar(leftX, eyeY + state.leftBlinkLevel, leftWidth, leftHeight, Colors::Cyan);
  FaceCommon::drawEyeBar(rightX, eyeY + state.rightBlinkLevel, rightWidth, rightHeight, Colors::Cyan);
}

void drawMouth() {
  const FaceState::RenderState& state = FaceState::current();
  const int width = max(34, 60 + state.mouthWidthDelta);
  const int mouthY = FaceCommon::kMouthY + state.mouthOffsetY;

  FaceCommon::drawFlatMouth(FaceCommon::kMouthCenterX, mouthY, width, Colors::Cyan, 5);
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

}  // namespace FaceSleepy
