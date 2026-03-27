#pragma once

#include <Arduino.h>

namespace FaceGallery {

/// Initialize the gallery and draw the initial face.
void begin();
/// Advance animation and redraw work for the currently selected face.
void update(unsigned long now);
/// Switch to the next face in the gallery.
void next();
/// Switch to the previous face in the gallery.
void previous();
/// Select a face by zero-based gallery index.
bool setByIndex(uint8_t index);
/// Select a face by its stable command / gallery name.
bool setByName(const char* name);
/// Redraw the full current face.
void drawCurrent();
/// Redraw only the current face's eye region.
void drawEyesCurrent();
/// Redraw only the current face's mouth region.
void drawMouthCurrent();
/// Redraw the current face using its blink variant.
void drawBlinkCurrent();
/// Return the current face name.
const char* currentName();
/// Return the zero-based index of the current face.
uint8_t currentIndex();
/// Return the number of registered faces in the gallery.
uint8_t faceCount();

}  // namespace FaceGallery
