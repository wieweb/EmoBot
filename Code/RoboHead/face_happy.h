#pragma once

namespace FaceHappy {
/// Draw the full happy face into the current render target.
void draw();
/// Redraw only the happy eye region.
void drawEyes();
/// Redraw only the happy mouth region.
void drawMouth();
/// Draw the blink variant for the happy face.
void drawBlink();
}
