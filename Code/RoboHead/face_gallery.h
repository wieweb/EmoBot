#pragma once

#include <Arduino.h>

namespace FaceGallery {

void begin();
void update(unsigned long now);
void next();
void previous();
void drawCurrent();
void drawEyesCurrent();
void drawBlinkCurrent();
const char* currentName();
uint8_t currentIndex();
uint8_t faceCount();

}  // namespace FaceGallery
