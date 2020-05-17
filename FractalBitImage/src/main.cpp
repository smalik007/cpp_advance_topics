/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>

#include "BitMap.h"
#include "MandelBrot.h"

using namespace std;

int main() {
  const int WIDTH = 800;
  const int HEIGHT = 600;

  double xMin = INT32_MAX;
  double xMax = INT32_MIN;

  double yMin = INT32_MAX;
  double yMax = INT32_MIN;

  CreateBitMap::BitMap bitMap(WIDTH, HEIGHT);

  // bitMap.setPixel(WIDTH / 2, HEIGHT / 2, 255, 255, 255);

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      // bitMap.setPixel(x, y, 255, 0, 0); /* write a complete Red Bitmap file */

      double xFractal = (x - WIDTH / 2 - 200) * (2.0 / HEIGHT); /* convert and get the range in -1 to +1 range , symmetric about 0 */
      double yFractal = (y - HEIGHT / 2) * (2.0 / HEIGHT);

      int iteration = FractalBitMap::MandelBrot::getIteration(xFractal, yFractal);
      uint8_t colorIt = (uint8_t)(256 * (double)iteration / FractalBitMap::MandelBrot::MAX_ITERATIONS);
      /* when itr return 1000 the color value would be 256  */
      /* In other case it usually be just black */

      colorIt = colorIt * colorIt * colorIt; /* Some random stuff to get random pattern */
      // colorIt = colorIt * colorIt * 124 * 17671;

      bitMap.setPixel(x, y, 0, colorIt, colorIt);

      if (xFractal < xMin) xMin = xFractal;
      if (xFractal > xMax) xMax = xFractal;

      if (yFractal < yMin) yMin = yFractal;
      if (yFractal > yMax) yMax = yFractal;
    }
  }

  cout << "xMin : " << xMin << " , xMax : " << xMax << endl;
  cout << "yMin : " << yMin << " , yMax : " << yMax << endl;

  if (bitMap.write("test.bmp")) {
    cout << "BitMap Created Successully" << endl;
  } else {
    cout << "Failure in writing Bitmap" << endl;
  }

  return 0;
}
