#pragma once

namespace FaceNeutral {
/// Draw the full neutral face into the current render target.
void draw();
/// Redraw only the neutral eye region.
void drawEyes();
/// Redraw only the neutral mouth region.
void drawMouth();
/// Draw the blink variant for the neutral face.
void drawBlink();
}
