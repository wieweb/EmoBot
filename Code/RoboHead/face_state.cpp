#include "face_state.h"

namespace {

FaceState::RenderState g_state = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  FaceState::Mood::Calm,
};

uint8_t clampBlinkLevel(uint8_t level) {
  return (level > 2) ? 2 : level;
}

}  // namespace

namespace FaceState {

void reset() {
  g_state.eyeOffsetX = 0;
  g_state.eyeOffsetY = 0;
  g_state.eyeInsetX = 0;
  g_state.leftBlinkLevel = 0;
  g_state.rightBlinkLevel = 0;
  g_state.mouthOffsetY = 0;
  g_state.mouthWidthDelta = 0;
  g_state.mouthHeightDelta = 0;
  g_state.mouthRadiusDelta = 0;
  g_state.mood = Mood::Calm;
}

const RenderState& current() {
  return g_state;
}

void setEyeOffset(int x, int y) {
  g_state.eyeOffsetX = x;
  g_state.eyeOffsetY = y;
}

void setEyeInset(int insetX) {
  g_state.eyeInsetX = insetX;
}

void setBlinkLevels(uint8_t leftLevel, uint8_t rightLevel) {
  g_state.leftBlinkLevel = clampBlinkLevel(leftLevel);
  g_state.rightBlinkLevel = clampBlinkLevel(rightLevel);
}

void setMouthAdjustments(int offsetY, int widthDelta, int heightDelta, int radiusDelta) {
  g_state.mouthOffsetY = offsetY;
  g_state.mouthWidthDelta = widthDelta;
  g_state.mouthHeightDelta = heightDelta;
  g_state.mouthRadiusDelta = radiusDelta;
}

void setMood(Mood mood) {
  g_state.mood = mood;
}

}  // namespace FaceState
