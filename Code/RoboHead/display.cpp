#include "display.h"

#include <SPI.h>
#include <esp_heap_caps.h>

#include "colors.h"
#include "pins.h"

namespace {

class FrameBufferCanvas : public Adafruit_GFX {
 public:
  FrameBufferCanvas(uint16_t width, uint16_t height)
      : Adafruit_GFX(width, height), width_(width), height_(height) {
  }

  ~FrameBufferCanvas() override {
    if (buffer_ != nullptr) {
      free(buffer_);
    }
  }

  bool begin() {
    const size_t bytes = static_cast<size_t>(width_) * static_cast<size_t>(height_) * sizeof(uint16_t);
    buffer_ = static_cast<uint16_t*>(heap_caps_malloc(bytes, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT));
    if (buffer_ == nullptr) {
      buffer_ = static_cast<uint16_t*>(heap_caps_malloc(bytes, MALLOC_CAP_8BIT));
    }
    if (buffer_ == nullptr) {
      return false;
    }

    fillScreen(Colors::Black);
    return true;
  }

  void drawPixel(int16_t x, int16_t y, uint16_t color) override {
    if (buffer_ == nullptr || x < 0 || y < 0 || x >= width_ || y >= height_) {
      return;
    }
    buffer_[static_cast<size_t>(y) * width_ + x] = color;
  }

  void fillScreen(uint16_t color) override {
    if (buffer_ == nullptr) {
      return;
    }

    const size_t pixelCount = static_cast<size_t>(width_) * static_cast<size_t>(height_);
    for (size_t i = 0; i < pixelCount; ++i) {
      buffer_[i] = color;
    }
  }

  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) override {
    if (buffer_ == nullptr || w <= 0 || h <= 0) {
      return;
    }

    int16_t clippedX = x;
    int16_t clippedY = y;
    int16_t clippedW = w;
    int16_t clippedH = h;

    if (clippedX < 0) {
      clippedW += clippedX;
      clippedX = 0;
    }
    if (clippedY < 0) {
      clippedH += clippedY;
      clippedY = 0;
    }
    if ((clippedX + clippedW) > width_) {
      clippedW = width_ - clippedX;
    }
    if ((clippedY + clippedH) > height_) {
      clippedH = height_ - clippedY;
    }
    if (clippedW <= 0 || clippedH <= 0) {
      return;
    }

    for (int16_t row = 0; row < clippedH; ++row) {
      uint16_t* line = buffer_ + (static_cast<size_t>(clippedY + row) * width_) + clippedX;
      for (int16_t col = 0; col < clippedW; ++col) {
        line[col] = color;
      }
    }
  }

  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override {
    fillRect(x, y, w, 1, color);
  }

  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override {
    fillRect(x, y, 1, h, color);
  }

  uint16_t* buffer() {
    return buffer_;
  }

 private:
  uint16_t* buffer_ = nullptr;
  const int16_t width_;
  const int16_t height_;
};

Adafruit_ST7789 g_tft(TFT_CS, TFT_DC, TFT_RST);
FrameBufferCanvas g_canvas(Display::kScreenWidth, Display::kScreenHeight);
bool g_hasFrameBuffer = false;
}

namespace Display {

void begin() {
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

  g_tft.init(kPanelWidth, kPanelHeight);
  g_tft.setRotation(1);
  g_hasFrameBuffer = g_canvas.begin();

  if (g_hasFrameBuffer) {
    g_canvas.fillScreen(Colors::Black);
    present();
    return;
  }

  g_tft.fillScreen(Colors::Black);
}

void clear(uint16_t color) {
  if (g_hasFrameBuffer) {
    g_canvas.fillScreen(color);
    return;
  }

  g_tft.fillScreen(color);
}

void present() {
  if (!g_hasFrameBuffer) {
    return;
  }

  g_tft.startWrite();
  g_tft.setAddrWindow(0, 0, kScreenWidth, kScreenHeight);
  g_tft.writePixels(g_canvas.buffer(), static_cast<uint32_t>(kScreenWidth) * static_cast<uint32_t>(kScreenHeight));
  g_tft.endWrite();
}

bool hasFrameBuffer() {
  return g_hasFrameBuffer;
}

Adafruit_GFX& canvas() {
  return g_canvas;
}

Adafruit_ST7789& tft() {
  return g_tft;
}

}  // namespace Display
