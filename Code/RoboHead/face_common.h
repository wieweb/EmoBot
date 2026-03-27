#pragma once

#include <Arduino.h>

namespace FaceCommon {

constexpr int kEyeY = 86;
constexpr int kLeftEyeX = 72;
constexpr int kRightEyeX = 208;
constexpr int kMouthCenterX = 140;
constexpr int kMouthY = 182;

void clearCanvas();
void clearEyeArea();
void drawDotEye(int x, int y, int radius, uint16_t color);
void drawEyeBar(int x, int y, int width, int height, uint16_t color);
void drawClosedEyes(uint16_t color, int width, int height);
void drawHeartEye(int x, int y, int size, uint16_t color);
void drawOpenMouth(int x, int y, int radius, uint16_t color);
void drawFlatMouth(int x, int y, int width, uint16_t color, uint8_t thickness);
void drawSmile(int x, int y, int width, int height, uint16_t color, uint8_t thickness);
void drawFrown(int x, int y, int width, int height, uint16_t color, uint8_t thickness);
void drawQuadraticCurve(int x0, int y0, int cx, int cy, int x1, int y1, uint16_t color, uint8_t thickness);
void drawThickLine(int x0, int y0, int x1, int y1, uint16_t color, uint8_t thickness);

}  // namespace FaceCommon
