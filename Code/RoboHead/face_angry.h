#pragma once

namespace FaceAngry {
/// Draw the full angry face into the current render target.
void draw();
/// Redraw only the angry eye region.
void drawEyes();
/// Redraw only the angry mouth region.
void drawMouth();
/// Draw the blink variant for the angry face.
void drawBlink();
}
