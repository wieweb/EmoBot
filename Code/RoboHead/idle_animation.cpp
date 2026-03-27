#include "idle_animation.h"

#include "face_common.h"
#include "face_gallery.h"
#include "face_state.h"

namespace {

constexpr unsigned long kEyeStepMs = 45;
constexpr unsigned long kSaccadeEyeStepMs = 14;
constexpr unsigned long kMoodMinMs = 9000;
constexpr unsigned long kMoodMaxMs = 18000;
constexpr unsigned long kMicroMinMs = 3200;
constexpr unsigned long kMicroMaxMs = 7600;
constexpr unsigned long kMicroDurationMinMs = 1200;
constexpr unsigned long kMicroDurationMaxMs = 2600;
constexpr unsigned long kSaccadeMinMs = 1700;
constexpr unsigned long kSaccadeMaxMs = 4200;
constexpr unsigned long kSaccadeHoldMinMs = 45;
constexpr unsigned long kSaccadeHoldMaxMs = 95;
constexpr unsigned long kAttentionDurationMs = 900;
constexpr unsigned long kAttentionBlinkDelayMs = 70;

enum class MicroExpression : uint8_t {
  None,
  SoftSmile,
  Relaxed,
  CuriousPeek,
};

struct BlinkFrame {
  uint8_t leftLevel;
  uint8_t rightLevel;
  unsigned long durationMs;
};

BlinkFrame blinkFrames[8];
uint8_t blinkFrameCount = 0;
uint8_t blinkFrameIndex = 0;

FaceState::Mood currentMood = FaceState::Mood::Calm;
MicroExpression currentMicro = MicroExpression::None;

bool blinkSequenceActive = false;
bool saccadeActive = false;
bool attentionActive = false;
bool attentionBlinkQueued = false;
unsigned long nextBlinkFrameAt = 0;
unsigned long nextBlinkAt = 0;
unsigned long nextMoodChangeAt = 0;
unsigned long nextGazeAt = 0;
unsigned long nextEyeStepAt = 0;
unsigned long nextMicroAt = 0;
unsigned long microEndsAt = 0;
unsigned long nextSaccadeAt = 0;
unsigned long saccadeEndsAt = 0;
unsigned long attentionEndsAt = 0;
unsigned long attentionBlinkAt = 0;

int eyeCurrentX = 0;
int eyeCurrentY = 0;
int eyeTargetX = 0;
int eyeTargetY = 0;
int eyeInsetCurrent = 0;
int saccadeTargetX = 0;
int saccadeTargetY = 0;
int8_t attentionDirection = 0;

long randomRange(long minValue, long maxValue) {
  return random(minValue, maxValue + 1);
}

void redrawEyes() {
  FaceCommon::clearEyeArea();
  FaceGallery::drawEyesCurrent();
}

void redrawMouth() {
  FaceCommon::clearMouthArea();
  FaceGallery::drawMouthCurrent();
}

void scheduleNextSaccade(unsigned long now) {
  unsigned long minDelay = kSaccadeMinMs;
  unsigned long maxDelay = kSaccadeMaxMs;

  if (currentMood == FaceState::Mood::Curious) {
    minDelay = 900;
    maxDelay = 2200;
  } else if (currentMood == FaceState::Mood::Sleepy) {
    minDelay = 2800;
    maxDelay = 5200;
  } else if (currentMood == FaceState::Mood::Cheerful) {
    minDelay = 1300;
    maxDelay = 2600;
  }

  nextSaccadeAt = now + static_cast<unsigned long>(randomRange(minDelay, maxDelay));
}

void scheduleMoodChange(unsigned long now) {
  nextMoodChangeAt = now + static_cast<unsigned long>(randomRange(kMoodMinMs, kMoodMaxMs));
}

void scheduleMicroExpression(unsigned long now) {
  nextMicroAt = now + static_cast<unsigned long>(randomRange(kMicroMinMs, kMicroMaxMs));
}

void scheduleNextBlink(unsigned long now) {
  unsigned long minDelay = 2600;
  unsigned long maxDelay = 6200;

  if (currentMood == FaceState::Mood::Curious) {
    minDelay = 2200;
    maxDelay = 5000;
  } else if (currentMood == FaceState::Mood::Sleepy) {
    minDelay = 1500;
    maxDelay = 3600;
  } else if (currentMood == FaceState::Mood::Cheerful) {
    minDelay = 2400;
    maxDelay = 5200;
  }

  nextBlinkAt = now + static_cast<unsigned long>(randomRange(minDelay, maxDelay));
}

void scheduleNextGaze(unsigned long now) {
  unsigned long minDelay = 1800;
  unsigned long maxDelay = 4200;

  if (currentMood == FaceState::Mood::Curious) {
    minDelay = 1000;
    maxDelay = 2200;
  } else if (currentMood == FaceState::Mood::Sleepy) {
    minDelay = 2600;
    maxDelay = 5200;
  } else if (currentMood == FaceState::Mood::Cheerful) {
    minDelay = 1400;
    maxDelay = 3000;
  }

  nextGazeAt = now + static_cast<unsigned long>(randomRange(minDelay, maxDelay));
}

void applyMood(FaceState::Mood mood) {
  currentMood = mood;
  FaceState::setMood(mood);
}

void chooseSaccadeTarget() {
  int rangeXMin = 4;
  int rangeXMax = 7;
  int rangeYMin = -2;
  int rangeYMax = 2;

  if (currentMood == FaceState::Mood::Curious) {
    rangeXMin = 6;
    rangeXMax = 10;
    rangeYMin = -2;
    rangeYMax = 1;
  } else if (currentMood == FaceState::Mood::Sleepy) {
    rangeXMin = 3;
    rangeXMax = 5;
    rangeYMin = -1;
    rangeYMax = 2;
  }

  const int direction = (randomRange(0, 1) == 0) ? -1 : 1;
  saccadeTargetX = direction * static_cast<int>(randomRange(rangeXMin, rangeXMax));
  saccadeTargetY = static_cast<int>(randomRange(rangeYMin, rangeYMax));
}

FaceState::Mood randomMood() {
  const long roll = randomRange(0, 99);
  if (roll < 35) {
    return FaceState::Mood::Calm;
  }
  if (roll < 58) {
    return FaceState::Mood::Curious;
  }
  if (roll < 78) {
    return FaceState::Mood::Cheerful;
  }
  return FaceState::Mood::Sleepy;
}

MicroExpression randomMicroExpression() {
  if (currentMood == FaceState::Mood::Sleepy) {
    return (randomRange(0, 1) == 0) ? MicroExpression::Relaxed : MicroExpression::SoftSmile;
  }

  if (currentMood == FaceState::Mood::Curious) {
    return (randomRange(0, 1) == 0) ? MicroExpression::CuriousPeek : MicroExpression::SoftSmile;
  }

  if (currentMood == FaceState::Mood::Cheerful) {
    return (randomRange(0, 1) == 0) ? MicroExpression::SoftSmile : MicroExpression::CuriousPeek;
  }

  const long roll = randomRange(0, 2);
  if (roll == 0) {
    return MicroExpression::SoftSmile;
  }
  if (roll == 1) {
    return MicroExpression::Relaxed;
  }
  return MicroExpression::CuriousPeek;
}

void chooseGazeTarget() {
  int rangeX = 3;
  int rangeY = 1;
  const bool sideLook = randomRange(0, 99) < 28;

  if (currentMood == FaceState::Mood::Curious) {
    rangeX = 5;
    rangeY = 2;
  } else if (currentMood == FaceState::Mood::Sleepy) {
    rangeX = 2;
    rangeY = 2;
  } else if (currentMood == FaceState::Mood::Cheerful) {
    rangeX = 4;
    rangeY = 2;
  }

  if (sideLook) {
    const int sideDirection = (randomRange(0, 1) == 0) ? -1 : 1;
    if (currentMood == FaceState::Mood::Curious) {
      eyeTargetX = sideDirection * static_cast<int>(randomRange(6, 8));
      eyeTargetY = static_cast<int>(randomRange(-1, 1));
    } else if (currentMood == FaceState::Mood::Sleepy) {
      eyeTargetX = sideDirection * static_cast<int>(randomRange(4, 6));
      eyeTargetY = static_cast<int>(randomRange(0, 2));
    } else {
      eyeTargetX = sideDirection * static_cast<int>(randomRange(5, 7));
      eyeTargetY = static_cast<int>(randomRange(-1, 1));
    }
    return;
  }

  eyeTargetX = static_cast<int>(randomRange(-rangeX, rangeX));
  eyeTargetY = static_cast<int>(randomRange(-rangeY, rangeY));
}

void startSaccade(unsigned long now) {
  chooseSaccadeTarget();
  saccadeActive = true;
  saccadeEndsAt = now + static_cast<unsigned long>(randomRange(kSaccadeHoldMinMs, kSaccadeHoldMaxMs));
}

int stepToward(int current, int target) {
  if (current < target) {
    return current + 1;
  }
  if (current > target) {
    return current - 1;
  }
  return current;
}

int triangleWave(unsigned long now, unsigned long periodMs, int amplitude) {
  if (amplitude <= 0) {
    return 0;
  }

  const unsigned long halfPeriod = periodMs / 2;
  const unsigned long phase = now % periodMs;

  if (phase < halfPeriod) {
    return map(static_cast<long>(phase), 0, static_cast<long>(halfPeriod), -amplitude, amplitude);
  }

  return map(static_cast<long>(phase), static_cast<long>(halfPeriod), static_cast<long>(periodMs), amplitude, -amplitude);
}

void composeMouthAdjustments(unsigned long now, int& offsetY, int& widthDelta, int& heightDelta, int& radiusDelta) {
  offsetY = 0;
  widthDelta = 0;
  heightDelta = 0;
  radiusDelta = 0;

  switch (currentMood) {
    case FaceState::Mood::Calm:
      break;
    case FaceState::Mood::Curious:
      offsetY -= 1;
      widthDelta -= 2;
      heightDelta += 1;
      radiusDelta += 1;
      break;
    case FaceState::Mood::Sleepy:
      offsetY += 1;
      widthDelta -= 4;
      heightDelta -= 1;
      radiusDelta -= 1;
      break;
    case FaceState::Mood::Cheerful:
      widthDelta += 4;
      heightDelta += 2;
      radiusDelta += 1;
      break;
  }

  switch (currentMicro) {
    case MicroExpression::None:
      break;
    case MicroExpression::SoftSmile:
      widthDelta += 3;
      heightDelta += 2;
      break;
    case MicroExpression::Relaxed:
      offsetY += 1;
      heightDelta -= 1;
      break;
    case MicroExpression::CuriousPeek:
      offsetY -= 1;
      widthDelta -= 2;
      radiusDelta += 1;
      break;
  }

  const int breathY = triangleWave(now, 5600, 1);
  const int breathHeight = triangleWave(now + 900, 5600, (currentMood == FaceState::Mood::Cheerful) ? 2 : 1);
  offsetY += breathY;
  heightDelta += breathHeight;

  const int sidewaysLook = abs(eyeCurrentX);
  widthDelta -= sidewaysLook * 2;
  if (sidewaysLook >= 5) {
    heightDelta -= 1;
  }

  if (attentionActive) {
    widthDelta -= 4;
    heightDelta += 1;
  }
}

void composeEyeTarget(int& targetX, int& targetY) {
  if (attentionActive) {
    targetX = attentionDirection * 7;
    targetY = -2;
    return;
  }

  if (saccadeActive) {
    targetX = saccadeTargetX;
    targetY = saccadeTargetY;
    return;
  }

  targetX = eyeTargetX;
  targetY = eyeTargetY;

  switch (currentMood) {
    case FaceState::Mood::Calm:
      break;
    case FaceState::Mood::Curious:
      targetY -= 1;
      break;
    case FaceState::Mood::Sleepy:
      targetY += 1;
      break;
    case FaceState::Mood::Cheerful:
      targetY -= 1;
      break;
  }

  switch (currentMicro) {
    case MicroExpression::None:
      break;
    case MicroExpression::SoftSmile:
      targetY -= 1;
      break;
    case MicroExpression::Relaxed:
      targetY += 1;
      break;
    case MicroExpression::CuriousPeek:
      targetX += (eyeTargetX >= 0) ? 1 : -1;
      targetY -= 1;
      break;
  }
}

void setBlinkFrame(uint8_t index, uint8_t left, uint8_t right, unsigned long durationMs) {
  blinkFrames[index].leftLevel = left;
  blinkFrames[index].rightLevel = right;
  blinkFrames[index].durationMs = durationMs;
}

void buildBlinkSequence() {
  blinkFrameCount = 0;
  blinkFrameIndex = 0;

  long roll = randomRange(0, 99);
  if (currentMood == FaceState::Mood::Sleepy) {
    roll += 15;
    if (roll > 99) {
      roll = 99;
    }
  }

  if (roll < 45) {
    setBlinkFrame(0, 1, 1, 45);
    setBlinkFrame(1, 2, 2, 70);
    setBlinkFrame(2, 1, 1, 45);
    setBlinkFrame(3, 0, 0, 0);
    blinkFrameCount = 4;
    return;
  }

  if (roll < 70) {
    setBlinkFrame(0, 1, 1, 40);
    setBlinkFrame(1, 2, 2, 55);
    setBlinkFrame(2, 1, 1, 40);
    setBlinkFrame(3, 0, 0, 110);
    setBlinkFrame(4, 1, 1, 40);
    setBlinkFrame(5, 2, 2, 55);
    setBlinkFrame(6, 1, 1, 40);
    setBlinkFrame(7, 0, 0, 0);
    blinkFrameCount = 8;
    return;
  }

  if (roll < 88) {
    setBlinkFrame(0, 1, 0, 35);
    setBlinkFrame(1, 2, 1, 45);
    setBlinkFrame(2, 2, 2, 40);
    setBlinkFrame(3, 1, 2, 40);
    setBlinkFrame(4, 0, 1, 35);
    setBlinkFrame(5, 0, 0, 0);
    blinkFrameCount = 6;
    return;
  }

  setBlinkFrame(0, 1, 1, 55);
  setBlinkFrame(1, 2, 2, 130);
  setBlinkFrame(2, 1, 1, 55);
  setBlinkFrame(3, 0, 0, 0);
  blinkFrameCount = 4;
}

void applyBlinkLevels(uint8_t leftLevel, uint8_t rightLevel) {
  const FaceState::RenderState& state = FaceState::current();
  if (state.leftBlinkLevel == leftLevel && state.rightBlinkLevel == rightLevel) {
    return;
  }

  FaceState::setBlinkLevels(leftLevel, rightLevel);
  redrawEyes();
}

void startBlinkSequence(unsigned long now) {
  buildBlinkSequence();
  blinkSequenceActive = true;
  nextBlinkFrameAt = now;
}

bool isBlinkNeutral() {
  const FaceState::RenderState& state = FaceState::current();
  return state.leftBlinkLevel == 0 && state.rightBlinkLevel == 0;
}

void updateBlink(unsigned long now) {
  if (!blinkSequenceActive) {
    if (now >= nextBlinkAt) {
      startBlinkSequence(now);
    }
    return;
  }

  if (now < nextBlinkFrameAt || blinkFrameIndex >= blinkFrameCount) {
    return;
  }

  const BlinkFrame& frame = blinkFrames[blinkFrameIndex];
  applyBlinkLevels(frame.leftLevel, frame.rightLevel);
  ++blinkFrameIndex;

  if (blinkFrameIndex >= blinkFrameCount) {
    blinkSequenceActive = false;
    scheduleNextBlink(now);
    return;
  }

  nextBlinkFrameAt = now + frame.durationMs;
}

void updateAttention(unsigned long now) {
  if (!attentionActive) {
    return;
  }

  if (attentionBlinkQueued && now >= attentionBlinkAt && !blinkSequenceActive && isBlinkNeutral()) {
    attentionBlinkQueued = false;
    startBlinkSequence(now);
  }

  if (now < attentionEndsAt) {
    return;
  }

  attentionActive = false;
  attentionDirection = 0;
  attentionBlinkQueued = false;
  scheduleNextGaze(now);
  scheduleNextSaccade(now);
}

void updateSaccade(unsigned long now) {
  if (attentionActive || blinkSequenceActive) {
    return;
  }

  if (saccadeActive) {
    if (now >= saccadeEndsAt && eyeCurrentX == saccadeTargetX && eyeCurrentY == saccadeTargetY) {
      saccadeActive = false;
      scheduleNextSaccade(now);
      scheduleNextGaze(now);
    }
    return;
  }

  if (now >= nextSaccadeAt) {
    startSaccade(now);
  }
}

void updateMoodAndMicro(unsigned long now) {
  if (now >= nextMoodChangeAt) {
    applyMood(randomMood());
    scheduleMoodChange(now);
    scheduleNextBlink(now);
    scheduleNextGaze(now);
    scheduleNextSaccade(now);
  }

  if (currentMicro != MicroExpression::None && now >= microEndsAt) {
    currentMicro = MicroExpression::None;
    scheduleMicroExpression(now);
  }

  if (currentMicro == MicroExpression::None && now >= nextMicroAt) {
    currentMicro = randomMicroExpression();
    microEndsAt = now + static_cast<unsigned long>(randomRange(kMicroDurationMinMs, kMicroDurationMaxMs));
  }
}

void updateGaze(unsigned long now) {
  if (now >= nextGazeAt) {
    chooseGazeTarget();
    scheduleNextGaze(now);
  }

  if (now < nextEyeStepAt) {
    return;
  }

  int composedTargetX = 0;
  int composedTargetY = 0;
  composeEyeTarget(composedTargetX, composedTargetY);

  const int nextX = stepToward(eyeCurrentX, composedTargetX);
  const int nextY = stepToward(eyeCurrentY, composedTargetY);
  const int targetInset = min(8, abs(composedTargetX));
  const int nextInset = stepToward(eyeInsetCurrent, targetInset);
  nextEyeStepAt = now + ((saccadeActive || attentionActive) ? kSaccadeEyeStepMs : kEyeStepMs);

  if (nextX == eyeCurrentX && nextY == eyeCurrentY && nextInset == eyeInsetCurrent) {
    return;
  }

  eyeCurrentX = nextX;
  eyeCurrentY = nextY;
  eyeInsetCurrent = nextInset;
  FaceState::setEyeOffset(eyeCurrentX, eyeCurrentY);
  FaceState::setEyeInset(eyeInsetCurrent);
  redrawEyes();
}

void updateMouth(unsigned long now) {
  int offsetY = 0;
  int widthDelta = 0;
  int heightDelta = 0;
  int radiusDelta = 0;
  composeMouthAdjustments(now, offsetY, widthDelta, heightDelta, radiusDelta);

  const FaceState::RenderState& state = FaceState::current();
  if (state.mouthOffsetY == offsetY &&
      state.mouthWidthDelta == widthDelta &&
      state.mouthHeightDelta == heightDelta &&
      state.mouthRadiusDelta == radiusDelta) {
    return;
  }

  FaceState::setMouthAdjustments(offsetY, widthDelta, heightDelta, radiusDelta);
  redrawMouth();
}

}  // namespace

namespace IdleAnimation {

void begin(unsigned long now) {
  randomSeed(static_cast<unsigned long>(micros()));
  FaceState::reset();
  applyMood(FaceState::Mood::Calm);
  currentMicro = MicroExpression::None;
  blinkSequenceActive = false;
  blinkFrameCount = 0;
  blinkFrameIndex = 0;
  eyeCurrentX = 0;
  eyeCurrentY = 0;
  eyeTargetX = 0;
  eyeTargetY = 0;
  eyeInsetCurrent = 0;
  nextBlinkFrameAt = 0;
  nextEyeStepAt = now;
  microEndsAt = 0;
  scheduleMoodChange(now);
  scheduleMicroExpression(now);
  scheduleNextBlink(now);
  scheduleNextGaze(now);
  scheduleNextSaccade(now);
  FaceState::setEyeOffset(0, 0);
  FaceState::setEyeInset(0);
  FaceState::setBlinkLevels(0, 0);
  FaceState::setMouthAdjustments(0, 0, 0, 0);
}

void update(unsigned long now) {
  updateAttention(now);
  updateMoodAndMicro(now);
  updateBlink(now);
  updateSaccade(now);
  updateGaze(now);
  updateMouth(now);
}

void notifyInteraction(unsigned long now) {
  blinkSequenceActive = false;
  blinkFrameCount = 0;
  blinkFrameIndex = 0;
  saccadeActive = false;
  currentMicro = MicroExpression::None;
  microEndsAt = 0;
  scheduleMicroExpression(now);
  FaceState::setBlinkLevels(0, 0);
  FaceState::setEyeInset(eyeInsetCurrent);
  scheduleNextBlink(now);
  scheduleNextGaze(now);
  scheduleNextSaccade(now);
}

void triggerAttention(unsigned long now, int8_t direction) {
  notifyInteraction(now);
  attentionActive = true;
  attentionDirection = (direction < 0) ? -1 : ((direction > 0) ? 1 : 0);
  attentionEndsAt = now + kAttentionDurationMs;
  attentionBlinkQueued = true;
  attentionBlinkAt = now + kAttentionBlinkDelayMs;
}

void triggerBlink(unsigned long now) {
  notifyInteraction(now);
  if (!blinkSequenceActive) {
    startBlinkSequence(now);
  }
}

}  // namespace IdleAnimation
