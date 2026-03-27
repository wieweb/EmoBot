#pragma once

namespace FaceSurprised {
/// Draw the full surprised face into the current render target.
void draw();
/// Redraw only the surprised eye region.
void drawEyes();
/// Redraw only the surprised mouth region.
void drawMouth();
/// Draw the blink variant for the surprised face.
void drawBlink();
}
