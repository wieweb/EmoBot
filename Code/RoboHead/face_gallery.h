#pragma once

#include <Arduino.h>

namespace FaceGallery {

void begin();
void next();
void previous();
void drawCurrent();
const char* currentName();
uint8_t currentIndex();
uint8_t faceCount();

}  // namespace FaceGallery
