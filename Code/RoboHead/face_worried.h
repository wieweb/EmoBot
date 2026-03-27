#pragma once

namespace FaceWorried {
/// Draw the full worried face into the current render target.
void draw();
/// Redraw only the worried eye region.
void drawEyes();
/// Redraw only the worried mouth region.
void drawMouth();
/// Draw the blink variant for the worried face.
void drawBlink();
}
