/*
 * Description - Zoom.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-24 02:36:32
 *
 */

#pragma once

namespace zoom {

struct Zoom {
  int x{0};
  int y{0};
  double scale{0.0};

  Zoom(int x, int y, double scale) : x(x), y(y), scale(scale) {}
};
}  // namespace zoom
