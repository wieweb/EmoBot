#pragma once

/// ST7789 chip select pin.
constexpr int TFT_CS = 10;
/// ST7789 data / command pin.
constexpr int TFT_DC = 9;
/// ST7789 reset pin.
constexpr int TFT_RST = 8;
/// SPI MOSI pin connected to the display.
constexpr int TFT_MOSI = 11;
/// SPI clock pin connected to the display.
constexpr int TFT_SCLK = 12;

/// Face-cycle button on the ESP32-S3 boot button pin.
constexpr int BUTTON_FACE = 0;  // BOOT button / GPIO0
