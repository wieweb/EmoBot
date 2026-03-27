#pragma once

namespace FaceSad {
/// Draw the full sad face into the current render target.
void draw();
/// Redraw only the sad eye region.
void drawEyes();
/// Redraw only the sad mouth region.
void drawMouth();
/// Draw the blink variant for the sad face.
void drawBlink();
}
