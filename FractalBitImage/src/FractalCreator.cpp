#include "FractalCreator.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>

namespace Fractal {
FractalCreator::FractalCreator(int width, int height)
    : _width(width), _height(height), _histogram(new int[FractalBitMap::MandelBrot::MAX_ITERATIONS]{}), _fractal(new int[width * height]{}), _bitMap(width, height), _zoomListObj(width, height) {}

FractalCreator::~FractalCreator() {}

void FractalCreator::calculateIteration(bool zoom) {
  int pixel_with_max_itr = 0;
  for (int y = 0; y < _height; y++) {
    for (int x = 0; x < _width; x++) {
      // bitMap.setPixel(x, y, 255, 0, 0); /* write a complete Red Bitmap file */

      int iteration = 0;
      if (zoom) {
        std::pair<double, double> coord = _zoomListObj.doZoom(x, y);
        iteration = FractalBitMap::MandelBrot::getIteration(coord.first, coord.second);
      } else {
        double x_fractal = (x - _width / 2 - 200) * (2.0 / _height); /* convert and get the range in -1 to +1 range , symmetric about 0 */
        double y_fractal = (y - _height / 2) * (2.0 / _height);
        iteration = FractalBitMap::MandelBrot::getIteration(x_fractal, y_fractal);
      }

      _fractal[y * _width + x] = iteration;
      if (iteration < FractalBitMap::MandelBrot::MAX_ITERATIONS) {
        _histogram[iteration]++; /* How many pixel (x,y) in the image get a perticular iteration value  */
      } else {
        pixel_with_max_itr++;
      }

      // uint8_t colorIt = (uint8_t)(256 * (double)iteration / _fractalBitMap::MandelBrot::MAX_ITERATIONS);
      /* when itr return 1000 the color value would be 256  */
      /* In other case it usually be just black */

      // colorIt = colorIt * colorIt * colorIt; /* Some random stuff to get random pattern */
      // colorIt = colorIt * colorIt * 124 * 17671;

      // bitMap.setPixel(x, y, 0, colorIt, colorIt);
    }  // for x
  }    // for y

  /* Validate _histogram */
  /* _histogram we created represent how many pixel (x,y) got the same iteration value*/
  /* So if we add up the all the _histogram array it will be equal to the total no of pixel in the bit map */
  /* but in _histogram we have not added the pixel which have max_iteration value, so we need also add that up*/

  // int total_pixel = 0;
  // for (int i = 0; i < _fractalBitMap::MandelBrot::MAX_ITERATIONS; ++i) {
  //   cout << _histogram[i] << "\t";
  //   total_pixel += _histogram[i];
  // }
  // cout << endl;
  // cout << total_pixel + pixel_with_max_itr << "," << _width * _height << endl;
}
void FractalCreator::drawFractal() {
  int total = 0;
  for (int i = 0; i < FractalBitMap::MandelBrot::MAX_ITERATIONS; i++) {
    total += _histogram[i];
  }

  for (int y = 0; y < _height; y++) {
    for (int x = 0; x < _width; x++) {
      int iteration = _fractal[y * _width + x];
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
          hue += (double)_histogram[i] / total;
        }
        /* This loop will give either some fractional value for hue or = 1, in that case pow(255, hue) will be betwenn some value to max 255 */
      }

      // green = pow(128, hue);
      // blue = pow(255, hue);
      red = pow(255, hue);

      _bitMap.setPixel(x, y, red, green, blue);
    }
  }
}
void FractalCreator::addZoom(const zoom::Zoom& obj) {
  _zoomListObj.add(zoom::Zoom(_width / 2, _height / 2, (4.0 / _width)));
  _zoomListObj.add(obj);
}
void FractalCreator::writeBitMap(const std::string& name) {
  if (_bitMap.write(name)) {
    cout << "BitMap Created Successully" << endl;
  } else {
    cout << "Failure in writing Bitmap" << endl;
  }
}

}  // namespace Fractal