#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <math.h>

// =====================================================
// Display pins for ESP32-S3-Zero
// =====================================================
static const int TFT_CS   = 10;
static const int TFT_DC   = 9;
static const int TFT_RST  = 8;
static const int TFT_MOSI = 11;
static const int TFT_SCLK = 12;

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// =====================================================
// Display config
// =====================================================
static const int SCREEN_W = 240;
static const int SCREEN_H = 280;

// =====================================================
// Colors (RGB565)
// =====================================================
static const uint16_t COLOR_BG      = 0x0000; // Black
static const uint16_t COLOR_EYE     = 0x07FF; // Cyan
static const uint16_t COLOR_MOUTH   = 0xFFFF; // White

// =====================================================
// Face layout
// =====================================================
static const int LEFT_EYE_X   = 75;
static const int RIGHT_EYE_X  = 165;
static const int EYE_BASE_Y   = 110;

static const int EYE_WIDTH    = 44;
static const int EYE_HEIGHT   = 56;
static const int EYE_RADIUS   = 10;

static const int PUPIL_W      = 14;
static const int PUPIL_H      = 20;
static const int PUPIL_RADIUS = 5;

static const int MOUTH_W_BASE = 46;
static const int MOUTH_H_BASE = 8;
static const int MOUTH_X      = 120 - MOUTH_W_BASE / 2;
static const int MOUTH_Y      = 205;

// =====================================================
// Animation state
// =====================================================
float currentLookX = 0.0f;
float targetLookX  = 0.0f;

float currentLookY = 0.0f;
float targetLookY  = 0.0f;

// 0.0 = open, 1.0 = closed
float blinkAmount = 0.0f;

enum BlinkPhase {
  BLINK_IDLE,
  BLINK_CLOSING,
  BLINK_HOLD,
  BLINK_OPENING
};

BlinkPhase blinkPhase = BLINK_IDLE;

// double blink support
bool pendingSecondBlink = false;
unsigned long secondBlinkStartTime = 0;

// look behavior
enum LookMode {
  LOOKMODE_CENTER_HOLD,
  LOOKMODE_GLANCE_SIDE,
  LOOKMODE_RETURN_TO_CENTER
};

LookMode lookMode = LOOKMODE_CENTER_HOLD;

// =====================================================
// Timing
// =====================================================
unsigned long lastFrameTime = 0;
const unsigned long FRAME_INTERVAL_MS = 16; // ~60 FPS

unsigned long nextLookEventTime = 0;
unsigned long nextBlinkTime = 0;
unsigned long blinkHoldUntil = 0;

// =====================================================
// Helpers
// =====================================================
unsigned long randomRangeUL(unsigned long minValue, unsigned long maxValue) {
  return minValue + (unsigned long)random((long)(maxValue - minValue + 1));
}

float randomFloatRange(float minValue, float maxValue) {
  return minValue + ((float)random(0, 10000) / 9999.0f) * (maxValue - minValue);
}

float approach(float current, float target, float step) {
  if (current < target) {
    current += step;
    if (current > target) current = target;
  } else if (current > target) {
    current -= step;
    if (current < target) current = target;
  }
  return current;
}

bool isNear(float a, float b, float epsilon) {
  return fabsf(a - b) <= epsilon;
}

// =====================================================
// Scheduling
// =====================================================
void scheduleNextBlink(unsigned long now) {
  nextBlinkTime = now + randomRangeUL(2800, 7000);
}

void scheduleCenterHold(unsigned long now) {
  lookMode = LOOKMODE_CENTER_HOLD;
  nextLookEventTime = now + randomRangeUL(1200, 3000);
  targetLookX = 0.0f;
  targetLookY = randomFloatRange(-1.5f, 1.5f);
}

void scheduleSideGlance(unsigned long now) {
  lookMode = LOOKMODE_GLANCE_SIDE;
  nextLookEventTime = now + randomRangeUL(500, 1300);

  targetLookX = (random(0, 2) == 0) ? -10.0f : 10.0f;
  targetLookY = randomFloatRange(-3.0f, 3.0f);
}

void scheduleReturnToCenter(unsigned long now) {
  lookMode = LOOKMODE_RETURN_TO_CENTER;
  nextLookEventTime = now + randomRangeUL(700, 1800);
  targetLookX = 0.0f;
  targetLookY = randomFloatRange(-1.5f, 1.5f);
}

// =====================================================
// Drawing
// =====================================================
void drawSingleEye(int centerX, int centerY, int pupilOffsetX, int pupilOffsetY, float blink) {
  int currentHeight = (int)((float)EYE_HEIGHT * (1.0f - blink));
  if (currentHeight < 6) currentHeight = 6;

  int eyeX = centerX - EYE_WIDTH / 2;
  int eyeY = centerY - currentHeight / 2;

  tft.fillRoundRect(
    eyeX,
    eyeY,
    EYE_WIDTH,
    currentHeight,
    EYE_RADIUS,
    COLOR_EYE
  );

  if (currentHeight <= 10) {
    return;
  }

  int innerMargin = 6;
  int innerW = EYE_WIDTH - innerMargin * 2;
  int innerH = currentHeight - innerMargin * 2;
  if (innerH < 2) innerH = 2;

  tft.fillRoundRect(
    centerX - innerW / 2,
    centerY - innerH / 2,
    innerW,
    innerH,
    EYE_RADIUS,
    COLOR_BG
  );

  int pupilTravelLimitX = (innerW / 2) - (PUPIL_W / 2) - 2;
  if (pupilOffsetX < -pupilTravelLimitX) pupilOffsetX = -pupilTravelLimitX;
  if (pupilOffsetX >  pupilTravelLimitX) pupilOffsetX =  pupilTravelLimitX;

  int pupilTravelLimitY = (innerH / 2) - (PUPIL_H / 2) - 1;
  if (pupilTravelLimitY < 0) pupilTravelLimitY = 0;
  if (pupilOffsetY < -pupilTravelLimitY) pupilOffsetY = -pupilTravelLimitY;
  if (pupilOffsetY >  pupilTravelLimitY) pupilOffsetY =  pupilTravelLimitY;

  int pupilX = centerX - PUPIL_W / 2 + pupilOffsetX;
  int pupilY = centerY - PUPIL_H / 2 + pupilOffsetY;

  tft.fillRoundRect(
    pupilX,
    pupilY,
    PUPIL_W,
    PUPIL_H,
    PUPIL_RADIUS,
    COLOR_EYE
  );
}

void drawMouth(unsigned long now) {
  // subtle breathing animation
  float breath = sinf((float)now * 0.0025f);
  int mouthW = MOUTH_W_BASE + (int)(breath * 2.0f);
  int mouthH = MOUTH_H_BASE + (int)((breath + 1.0f) * 0.5f * 2.0f);

  if (mouthW < 40) mouthW = 40;
  if (mouthH < 6) mouthH = 6;

  int mouthX = 120 - mouthW / 2;
  int mouthY = MOUTH_Y;

  tft.fillRoundRect(mouthX, mouthY, mouthW, mouthH, 4, COLOR_MOUTH);
}

void drawFace(unsigned long now) {
  tft.fillScreen(COLOR_BG);

  int pupilOffsetX = (int)currentLookX;
  int pupilOffsetY = (int)currentLookY;

  drawSingleEye(LEFT_EYE_X, EYE_BASE_Y, pupilOffsetX, pupilOffsetY, blinkAmount);
  drawSingleEye(RIGHT_EYE_X, EYE_BASE_Y, pupilOffsetX, pupilOffsetY, blinkAmount);
  drawMouth(now);
}

// =====================================================
// Animation updates
// =====================================================
void updateLookAnimation(unsigned long now) {
  if (now >= nextLookEventTime) {
    switch (lookMode) {
      case LOOKMODE_CENTER_HOLD:
        scheduleSideGlance(now);
        break;

      case LOOKMODE_GLANCE_SIDE:
        scheduleReturnToCenter(now);
        break;

      case LOOKMODE_RETURN_TO_CENTER:
      default:
        scheduleCenterHold(now);
        break;
    }
  }

  // smooth movement
  currentLookX = approach(currentLookX, targetLookX, 0.35f);
  currentLookY = approach(currentLookY, targetLookY, 0.20f);

  // tiny idle drift while centered
  if (lookMode == LOOKMODE_CENTER_HOLD && isNear(targetLookX, 0.0f, 0.1f)) {
    float idleDrift = sinf((float)now * 0.0018f) * 0.8f;
    currentLookY = idleDrift;
  }
}

void startBlink() {
  blinkPhase = BLINK_CLOSING;
}

void updateBlinkAnimation(unsigned long now) {
  if (blinkPhase == BLINK_IDLE && pendingSecondBlink && now >= secondBlinkStartTime) {
    pendingSecondBlink = false;
    startBlink();
  }

  switch (blinkPhase) {
    case BLINK_IDLE:
      if (now >= nextBlinkTime) {
        startBlink();
      }
      break;

    case BLINK_CLOSING:
      blinkAmount += 0.10f;
      if (blinkAmount >= 1.0f) {
        blinkAmount = 1.0f;
        blinkPhase = BLINK_HOLD;
        blinkHoldUntil = now + randomRangeUL(35, 80);
      }
      break;

    case BLINK_HOLD:
      if (now >= blinkHoldUntil) {
        blinkPhase = BLINK_OPENING;
      }
      break;

    case BLINK_OPENING:
      blinkAmount -= 0.10f;
      if (blinkAmount <= 0.0f) {
        blinkAmount = 0.0f;
        blinkPhase = BLINK_IDLE;

        // small chance for a double blink
        if (random(0, 100) < 22) {
          pendingSecondBlink = true;
          secondBlinkStartTime = now + randomRangeUL(90, 220);
        } else {
          pendingSecondBlink = false;
          scheduleNextBlink(now);
        }

        if (!pendingSecondBlink) {
          scheduleNextBlink(now);
        }
      }
      break;
  }
}

// =====================================================
// Setup / Loop
// =====================================================
void setup() {
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

  tft.init(240, 280);
  tft.setRotation(0);
  tft.fillScreen(COLOR_BG);

  randomSeed(micros());

  unsigned long now = millis();
  scheduleCenterHold(now);
  scheduleNextBlink(now);

  drawFace(now);
}

void loop() {
  unsigned long now = millis();

  if (now - lastFrameTime >= FRAME_INTERVAL_MS) {
    lastFrameTime = now;

    updateLookAnimation(now);
    updateBlinkAnimation(now);
    drawFace(now);
  }
}