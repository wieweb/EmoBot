#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

namespace Display {

constexpr int kPanelWidth = 240;
constexpr int kPanelHeight = 280;
constexpr int kScreenWidth = 280;
constexpr int kScreenHeight = 240;

void begin();
void clear(uint16_t color);
void present();
bool hasFrameBuffer();
Adafruit_GFX& canvas();
Adafruit_ST7789& tft();

}  // namespace Display
