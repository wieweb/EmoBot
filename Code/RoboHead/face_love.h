#pragma once

namespace FaceLove {
/// Draw the full love face into the current render target.
void draw();
/// Redraw only the love eye region.
void drawEyes();
/// Redraw only the love mouth region.
void drawMouth();
/// Draw the blink variant for the love face.
void drawBlink();
}
