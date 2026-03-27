#pragma once

#include <Arduino.h>

namespace FaceState {

/// High-level idle mood that slightly biases facial behavior.
enum class Mood : uint8_t {
  Calm,
  Curious,
  Sleepy,
  Cheerful,
};

/// Shared transient render state applied on top of the base face geometry.
struct RenderState {
  /// Horizontal eye offset used for gaze shifts.
  int eyeOffsetX;
  /// Vertical eye offset used for gaze shifts.
  int eyeOffsetY;
  /// Symmetric inward eye movement used during side looks.
  int eyeInsetX;
  /// Blink stage for the left eye.
  uint8_t leftBlinkLevel;
  /// Blink stage for the right eye.
  uint8_t rightBlinkLevel;
  /// Vertical mouth offset used for micro motion.
  int mouthOffsetY;
  /// Width adjustment for the current mouth shape.
  int mouthWidthDelta;
  /// Height adjustment for curved mouth shapes.
  int mouthHeightDelta;
  /// Radius adjustment for open mouth shapes.
  int mouthRadiusDelta;
  /// Current global mood selection.
  Mood mood;
};

/// Reset the transient render state to its default values.
void reset();
/// Return the current shared render state.
const RenderState& current();
/// Set the current eye offset used by face renderers.
void setEyeOffset(int x, int y);
/// Set the symmetric eye inset used during stronger side glances.
void setEyeInset(int insetX);
/// Set the current blink stage for both eyes.
void setBlinkLevels(uint8_t leftLevel, uint8_t rightLevel);
/// Set the current transient mouth adjustments.
void setMouthAdjustments(int offsetY, int widthDelta, int heightDelta, int radiusDelta);
/// Set the current high-level mood.
void setMood(Mood mood);

}  // namespace FaceState
