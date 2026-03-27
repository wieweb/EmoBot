#pragma once

namespace FaceLaugh {
/// Draw the full laughing face into the current render target.
void draw();
/// Redraw only the laughing eye region.
void drawEyes();
/// Redraw only the laughing mouth region.
void drawMouth();
/// Draw the blink variant for the laughing face.
void drawBlink();
}
