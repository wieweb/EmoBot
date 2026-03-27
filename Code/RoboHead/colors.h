#pragma once

#include <Arduino.h>

namespace Colors {

/// Primary cyan used for most face strokes and fills.
constexpr uint16_t Cyan = 0x07FF;
/// Accent pink used for love / heart eye details.
constexpr uint16_t Pink = 0xF8B3;
/// White highlight color for glossy eye details.
constexpr uint16_t White = 0xFFFF;
/// Background / clear color for the framebuffer.
constexpr uint16_t Black = 0x0000;

}  // namespace Colors
