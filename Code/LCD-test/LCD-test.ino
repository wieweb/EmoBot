#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// Pin assignment for ESP32-S3-Zero
static const int TFT_CS   = 10;
static const int TFT_DC   = 9;
static const int TFT_RST  = 8;
static const int TFT_MOSI = 11;
static const int TFT_SCLK = 12;

// ST7789: no MISO needed
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void drawTestPattern() {
  tft.fillScreen(ST77XX_BLACK);

  int w = tft.width();
  int h = tft.height();

  uint16_t myColor = tft.color565(255, 128, 0); // Orange

  // Four color blocks
  tft.fillRect(0,     0,     w / 2, h / 2, ST77XX_RED);
  tft.fillRect(w / 2, 0,     w / 2, h / 2, ST77XX_GREEN);
  tft.fillRect(0,     h / 2, w / 2, h / 2, ST77XX_BLUE);
  tft.fillRect(w / 2, h / 2, w / 2, h / 2, ST77XX_YELLOW);

  // White frame
  tft.drawRect(0, 0, w, h, ST77XX_WHITE);

  // Text
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 20);
  tft.println("LCD TEST");

  tft.setCursor(20, 50);
  tft.println("ESP32-S3-Zero");

  //tft.setTextSize(3);
  //tft.setCursor(20, 100);
  //tft.println("Hallo Tobias");
  //tft.setCursor(20, 125);
  //tft.println("Viel spass");
  //tft.setCursor(20, 150);
  //tft.println("beim bauen");

  // Cross lines
  tft.drawLine(0, 0, w - 1, h - 1, ST77XX_WHITE);
  tft.drawLine(w - 1, 0, 0, h - 1, ST77XX_WHITE);

  // Center circle
  tft.drawCircle(w / 2, h / 2, 30, ST77XX_CYAN);
  tft.fillCircle(w / 2, h / 2, 30, 0x46E8);
}

void setup() {
  // Start SPI with custom pins
  SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

  // 240x280 ST7789
  tft.init(240, 280);
  tft.setRotation(2);

  drawTestPattern();
}

void loop() {
}