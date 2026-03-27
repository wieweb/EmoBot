#include "face_common.h"

#include "colors.h"
#include "display.h"

namespace {
void fillVerticalPillGlow(int x, int y, int width, int height, uint16_t color) {
  Adafruit_ST7789& tft = Display::tft();
  const int cornerRadius = width / 2;
  tft.fillRoundRect(x - width / 2, y - height / 2, width, height, cornerRadius, color);
  tft.fillRoundRect(
    x - width / 2 + 2,
    y - height / 2 + 3,
    max(2, width / 3),
    max(4, height / 3),
    max(1, width / 6),
    Colors::White
  );
}

}  // namespace

namespace FaceCommon {

void clearCanvas() {
  Display::clear(Colors::Black);
}

void drawDotEye(int x, int y, int radius, uint16_t color) {
  const int width = max(16, radius + 10);
  const int height = max(40, (radius * 4) - 2);
  fillVerticalPillGlow(x, y, width, height, color);
}

void drawEyeBar(int x, int y, int width, int height, uint16_t color) {
  Adafruit_ST7789& tft = Display::tft();
  tft.fillRoundRect(x - width / 2, y - height / 2, width, height, height / 2, color);
}

void drawHeartEye(int x, int y, int size, uint16_t color) {
  Adafruit_ST7789& tft = Display::tft();
  const int lobeRadius = size / 3;
  const int offset = size / 4;

  tft.fillCircle(x - offset, y - offset / 2, lobeRadius, color);
  tft.fillCircle(x + offset, y - offset / 2, lobeRadius, color);
  tft.fillTriangle(
    x - size / 2,
    y,
    x + size / 2,
    y,
    x,
    y + size / 2 + 6,
    color
  );
}

void drawOpenMouth(int x, int y, int radius, uint16_t color) {
  Adafruit_ST7789& tft = Display::tft();
  tft.fillCircle(x, y, radius, color);
  tft.fillCircle(x, y, radius / 2, Colors::Black);
}

void drawFlatMouth(int x, int y, int width, uint16_t color, uint8_t thickness) {
  drawThickLine(x - width / 2, y, x + width / 2, y, color, thickness);
}

void drawSmile(int x, int y, int width, int height, uint16_t color, uint8_t thickness) {
  drawQuadraticCurve(x - width / 2, y - height / 3, x, y + height / 2, x + width / 2, y - height / 3, color, thickness);
}

void drawFrown(int x, int y, int width, int height, uint16_t color, uint8_t thickness) {
  drawQuadraticCurve(x - width / 2, y + height / 3, x, y - height / 2, x + width / 2, y + height / 3, color, thickness);
}

void drawQuadraticCurve(int x0, int y0, int cx, int cy, int x1, int y1, uint16_t color, uint8_t thickness) {
  float lastX = static_cast<float>(x0);
  float lastY = static_cast<float>(y0);

  for (int step = 1; step <= 24; ++step) {
    const float t = static_cast<float>(step) / 24.0f;
    const float u = 1.0f - t;
    const float x = (u * u * x0) + (2.0f * u * t * cx) + (t * t * x1);
    const float y = (u * u * y0) + (2.0f * u * t * cy) + (t * t * y1);
    drawThickLine(static_cast<int>(lastX), static_cast<int>(lastY), static_cast<int>(x), static_cast<int>(y), color, thickness);
    lastX = x;
    lastY = y;
  }
}

void drawThickLine(int x0, int y0, int x1, int y1, uint16_t color, uint8_t thickness) {
  Adafruit_ST7789& tft = Display::tft();
  const int dx = x1 - x0;
  const int dy = y1 - y0;
  const int steps = max(abs(dx), abs(dy));

  if (steps == 0) {
    tft.fillCircle(x0, y0, thickness / 2, color);
    return;
  }

  for (int step = 0; step <= steps; ++step) {
    const float t = static_cast<float>(step) / static_cast<float>(steps);
    const int x = x0 + static_cast<int>(dx * t);
    const int y = y0 + static_cast<int>(dy * t);
    tft.fillCircle(x, y, thickness / 2, color);
  }
}

}  // namespace FaceCommon
