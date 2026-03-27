#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

namespace Display {

/// Physical ST7789 panel width before rotation.
constexpr int kPanelWidth = 240;
/// Physical ST7789 panel height before rotation.
constexpr int kPanelHeight = 280;
/// Logical drawing width after applying the firmware rotation.
constexpr int kScreenWidth = 280;
/// Logical drawing height after applying the firmware rotation.
constexpr int kScreenHeight = 240;

/// Initialize SPI, the display controller, and the optional framebuffer.
void begin();
/// Clear the active render target with a solid color.
void clear(uint16_t color);
/// Transfer the completed framebuffer to the LCD when buffering is enabled.
void present();
/// Return whether a fullscreen framebuffer is available.
bool hasFrameBuffer();
/// Return the current drawing surface used by face renderers.
Adafruit_GFX& canvas();
/// Return direct access to the underlying ST7789 driver.
Adafruit_ST7789& tft();

}  // namespace Display
