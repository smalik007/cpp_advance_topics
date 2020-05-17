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
#include <memory>

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
  unique_ptr<int[]> histogram(new int[FractalBitMap::MandelBrot::MAX_ITERATIONS]{});
  unique_ptr<int[]> fractal(new int[WIDTH * HEIGHT]{});
  int pixel_with_max_itr = 0;
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      // bitMap.setPixel(x, y, 255, 0, 0); /* write a complete Red Bitmap file */

      double xFractal = (x - WIDTH / 2 - 200) * (2.0 / HEIGHT); /* convert and get the range in -1 to +1 range , symmetric about 0 */
      double yFractal = (y - HEIGHT / 2) * (2.0 / HEIGHT);

      int iteration = FractalBitMap::MandelBrot::getIteration(xFractal, yFractal);
      fractal[y * WIDTH + x] = iteration;
      if (iteration < FractalBitMap::MandelBrot::MAX_ITERATIONS) {
        histogram[iteration]++; /* How many pixel (x,y) in the image get a perticular iteration value  */
      } else {
        pixel_with_max_itr++;
      }

      // uint8_t colorIt = (uint8_t)(256 * (double)iteration / FractalBitMap::MandelBrot::MAX_ITERATIONS);
      /* when itr return 1000 the color value would be 256  */
      /* In other case it usually be just black */

      // colorIt = colorIt * colorIt * colorIt; /* Some random stuff to get random pattern */
      // colorIt = colorIt * colorIt * 124 * 17671;

      // bitMap.setPixel(x, y, 0, colorIt, colorIt);

      if (xFractal < xMin) xMin = xFractal;
      if (xFractal > xMax) xMax = xFractal;

      if (yFractal < yMin) yMin = yFractal;
      if (yFractal > yMax) yMax = yFractal;
    }
  }

  // cout << "xMin : " << xMin << " , xMax : " << xMax << endl;
  // cout << "yMin : " << yMin << " , yMax : " << yMax << endl;

  /* Validate Histogram */
  /* Histogram we created represent how many pixel (x,y) got the same iteration value*/
  /* So if we add up the all the histogram array it will be equal to the total no of pixel in the bit map */
  /* but in histogram we have not added the pixel which have max_iteration value, so we need also add that up*/

  // int total_pixel = 0;
  // for (int i = 0; i < FractalBitMap::MandelBrot::MAX_ITERATIONS; ++i) {
  //   cout << histogram[i] << "\t";
  //   total_pixel += histogram[i];
  // }
  // cout << endl;
  // cout << total_pixel + pixel_with_max_itr << "," << WIDTH * HEIGHT << endl;

  int total = 0;
  for (int i = 0; i < FractalBitMap::MandelBrot::MAX_ITERATIONS; i++) {
    total += histogram[i];
  }

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int iteration = fractal[y * WIDTH + x];
      double hue = 0.0;
      uint8_t red = 0;
      uint8_t green = 0;
      uint8_t blue = 0;

      /* all points that reached maximum iteration would be bounded, so all the green/blue/red are valued as 0, so pow(255, 0) will be = 1 and color would be blackish (inside the mandelbrot set)*/
      /* Also note that initialliy all the pixels were set to black hence the pixel out the range of -2 to 2 will already be black */
      /* What we are perticularly interested in are the edge points where the pixel get unbounded and want to color that */
      /* while when the iteration returns some value  */
      if (iteration != FractalBitMap::MandelBrot::MAX_ITERATIONS) {
        /* will never go to MAX_ITERATION = 1000 itr */
        for (int i = 0; i < iteration; i++) {
          hue += (double)histogram[i] / total;
        }
        /* This loop will give either some fractional value for hue or = 1, in that case pow(255, hue) will be betwenn some value to max 255 */
      }

      green = pow(255, hue);
      blue = pow(255, hue);

      bitMap.setPixel(x, y, red, green, blue);
    }
  }

  if (bitMap.write("test.bmp")) {
    cout << "BitMap Created Successully" << endl;
  } else {
    cout << "Failure in writing Bitmap" << endl;
  }

  return 0;
}
