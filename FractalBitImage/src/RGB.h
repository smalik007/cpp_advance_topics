/*
 * Description - RGB.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-24 23:58:36
 *
 */

#pragma once

namespace rgb {
struct RGB {
  int r;
  int g;
  int b;

  RGB(int r, int g, int b);
};

RGB operator-(const RGB& first, const RGB& second);

}  // namespace rgb
