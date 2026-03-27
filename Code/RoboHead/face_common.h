#pragma once

#include <Arduino.h>

namespace FaceCommon {

/// Shared Y position for the eye baseline.
constexpr int kEyeY = 86;
/// Shared default X position of the left eye center.
constexpr int kLeftEyeX = 72;
/// Shared default X position of the right eye center.
constexpr int kRightEyeX = 208;
/// Shared X position of the mouth center.
constexpr int kMouthCenterX = 140;
/// Shared Y position of the mouth baseline.
constexpr int kMouthY = 182;

/// Clear the full render target to the background color.
void clearCanvas();
/// Clear the eye redraw region inside the current render target.
void clearEyeArea();
/// Clear the mouth redraw region inside the current render target.
void clearMouthArea();
/// Draw a circular eye primitive.
void drawDotEye(int x, int y, int radius, uint16_t color);
/// Draw a vertical pill eye that supports partial blink closing.
void drawBlinkablePillEye(int x, int y, int radius, uint16_t color, uint8_t blinkLevel);
/// Draw a rectangular eye bar used by sleepy or closed-eye styles.
void drawEyeBar(int x, int y, int width, int height, uint16_t color);
/// Draw both eyes in a fully closed state.
void drawClosedEyes(uint16_t color, int width, int height);
/// Draw a heart-shaped eye.
void drawHeartEye(int x, int y, int size, uint16_t color);
/// Draw an open circular mouth.
void drawOpenMouth(int x, int y, int radius, uint16_t color);
/// Draw a straight mouth line.
void drawFlatMouth(int x, int y, int width, uint16_t color, uint8_t thickness);
/// Draw an upward curved smile.
void drawSmile(int x, int y, int width, int height, uint16_t color, uint8_t thickness);
/// Draw a downward curved frown.
void drawFrown(int x, int y, int width, int height, uint16_t color, uint8_t thickness);
/// Draw a quadratic curve by rasterizing it into thick line segments.
void drawQuadraticCurve(int x0, int y0, int cx, int cy, int x1, int y1, uint16_t color, uint8_t thickness);
/// Draw a straight line with configurable thickness.
void drawThickLine(int x0, int y0, int x1, int y1, uint16_t color, uint8_t thickness);

}  // namespace FaceCommon
