#include "display.h"

#include <SPI.h>

#include "colors.h"
#include "pins.h"

namespace {
Adafruit_ST7789 g_tft(TFT_CS, TFT_DC, TFT_RST);
}

namespace Display {

void begin() {
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

  g_tft.init(kPanelWidth, kPanelHeight);
  g_tft.setRotation(1);
  g_tft.fillScreen(Colors::Black);
}

void clear(uint16_t color) {
  g_tft.fillScreen(color);
}

Adafruit_ST7789& tft() {
  return g_tft;
}

}  // namespace Display
