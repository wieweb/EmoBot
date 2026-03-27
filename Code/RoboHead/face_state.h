#pragma once

#include <Arduino.h>

namespace FaceState {

enum class Mood : uint8_t {
  Calm,
  Curious,
  Sleepy,
  Cheerful,
};

struct RenderState {
  int eyeOffsetX;
  int eyeOffsetY;
  int eyeInsetX;
  uint8_t leftBlinkLevel;
  uint8_t rightBlinkLevel;
  int mouthOffsetY;
  int mouthWidthDelta;
  int mouthHeightDelta;
  int mouthRadiusDelta;
  Mood mood;
};

void reset();
const RenderState& current();
void setEyeOffset(int x, int y);
void setEyeInset(int insetX);
void setBlinkLevels(uint8_t leftLevel, uint8_t rightLevel);
void setMouthAdjustments(int offsetY, int widthDelta, int heightDelta, int radiusDelta);
void setMood(Mood mood);

}  // namespace FaceState
