#pragma once

namespace FaceSleepy {
/// Draw the full sleepy face into the current render target.
void draw();
/// Redraw only the sleepy eye region.
void drawEyes();
/// Redraw only the sleepy mouth region.
void drawMouth();
/// Draw the blink variant for the sleepy face.
void drawBlink();
}
