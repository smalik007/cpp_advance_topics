#include "RGB.h"

namespace rgb {
RGB::RGB(int r, int g, int b) : r(r), g(g), b(b) {}

RGB operator-(const RGB& first, const RGB& second) { return RGB(first.r - second.r, first.g - second.g, first.b - second.b); }

}  // namespace rgb