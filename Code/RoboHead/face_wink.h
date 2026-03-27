#pragma once

namespace FaceWink {
/// Draw the full wink face into the current render target.
void draw();
/// Redraw only the wink eye region.
void drawEyes();
/// Redraw only the wink mouth region.
void drawMouth();
/// Draw the blink variant for the wink face.
void drawBlink();
}
