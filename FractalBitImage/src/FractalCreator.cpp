#include "FractalCreator.h"

#include <assert.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>

#include "MandelBrot.h"

namespace Fractal {

FractalCreator::FractalCreator(int width, int height, bool zoom)
    : _width(width),
      _height(height),
      _histogram(new int[mandel::MandelBrot::MAX_ITERATIONS]{}),
      _fractal(new int[width * height]{}),
      _bitMap(width, height),
      _zoomListObj(width, height),
      _zoomFalg(zoom) {
  if (_zoomFalg) {
    _zoomListObj.add(zoom::Zoom(_width / 2, _height / 2, (4.0 / _width)));
  }
}

FractalCreator::~FractalCreator() {}

void FractalCreator::addZoom(const zoom::Zoom& obj) { _zoomListObj.add(obj); }

void FractalCreator::addColorGradientRange(double itrRange, const rgb::RGB& color) {
  _itrRange.push_back(itrRange * mandel::MandelBrot::MAX_ITERATIONS);
  _colorRange.push_back(color);

  if (_itrInit) {
    _totalItrForRange.push_back(0);
  }
  _itrInit = true;
}

int FractalCreator::getRangeIndx(int itr) const {
  int range = 0;

  for (int i = 1; i < _itrRange.size(); ++i) {
    range = i;
    if (_itrRange[i] > itr) {
      break;
    }
  }

  range--;

  assert(range > -1);
  assert(range < _itrRange.size());
  return range;
}

void FractalCreator::calculateIteration() {
  int pixel_with_max_itr = 0;
  for (int y = 0; y < _height; y++) {
    for (int x = 0; x < _width; x++) {
      // bitMap.setPixel(x, y, 255, 0, 0); /* write a complete Red Bitmap file */

      int iteration = 0;
      if (_zoomFalg) {
        std::pair<double, double> coord = _zoomListObj.doZoom(x, y);
        iteration = mandel::MandelBrot::getIteration(coord.first, coord.second);
      } else {
        double x_fractal = (x - _width / 2 - 200) * (2.0 / _height); /* convert and get the range in -1 to +1 range , symmetric about 0 */
        double y_fractal = (y - _height / 2) * (2.0 / _height);
        iteration = mandel::MandelBrot::getIteration(x_fractal, y_fractal);
      }

      _fractal[y * _width + x] = iteration;
      if (iteration != mandel::MandelBrot::MAX_ITERATIONS) {
        _histogram[iteration]++; /* How many pixel (x,y) in the image get a perticular iteration value  */
      } else {
        pixel_with_max_itr++;
      }

      // uint8_t colorIt = (uint8_t)(256 * (double)iteration / mandel::MandelBrot::MAX_ITERATIONS);
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

  //   int total_pixel = 0;
  //   for (int i = 0; i < mandel::MandelBrot::MAX_ITERATIONS; ++i) {
  //     // cout << _histogram[i] << "\t";
  //     total_pixel += _histogram[i];
  //   }
  //   cout << endl;
  //   cout << total_pixel << endl;
  //   cout << total_pixel + pixel_with_max_itr << "," << _width * _height << endl;
}

void FractalCreator::drawFractal() {
  int total = 0;
  for (int i = 0; i < mandel::MandelBrot::MAX_ITERATIONS; i++) {
    total += _histogram[i];
  }
  // cout << "total : " << total << endl;

  // rgb::RGB startColor(0, 0, 0);
  // rgb::RGB endColor(0, 255, 255);
  // rgb::RGB diffColor = endColor - startColor;

  for (int y = 0; y < _height; y++) {
    for (int x = 0; x < _width; x++) {
      int iteration = _fractal[y * _width + x];  // per pixel get iteration
      /* if iteration value is less 1000, it will be colored (it would be the unbounded points called the edges)
       otherwise if value > 1000 it is colored as black (these are the stable points and are called mandel brot set)  */
      double hue = 0.0;
      uint8_t red = 0;
      uint8_t green = 0;
      uint8_t blue = 0;

      int range = getRangeIndx(iteration);
      int totalItrInRange = _totalItrForRange[range];
      int rangeStart = _itrRange[range];

      rgb::RGB startColor = _colorRange[range];
      rgb::RGB endColor = _colorRange[range + 1];
      rgb::RGB diffColor = endColor - startColor;

      /* all points that reached maximum iteration would be bounded, so all the green/blue/red are valued as 0, so pow(255, 0) will be = 1 and color would be blackish (inside the mandelbrot set)*/
      /* Also note that initialliy all the pixels were set to black hence the pixel out the range of -2 to 2 will already be black */
      /* What we are perticularly interested in are the edge points where the pixel get unbounded and want to color that */
      /* while when the iteration returns some value  */
      if (iteration != mandel::MandelBrot::MAX_ITERATIONS) {
        for (int i = rangeStart; i <= iteration; i++) {
          // hue += (double)_histogram[i] / total;
          hue += _histogram[i];
        }
        /* This loop will give either some fractional value for hue or = 1, in that case pow(255, hue) will be betwenn some value to max 255 */
      }

      red = startColor.r + pow(diffColor.r, (double)(hue / totalItrInRange));
      green = startColor.g + pow(diffColor.g, (double)(hue / totalItrInRange));
      blue = startColor.b + pow(diffColor.b, (double)(hue / totalItrInRange));

      // green = pow(128, hue);
      // blue = pow(255, hue);
      //   red = pow(255, hue);

      _bitMap.setPixel(x, y, red, green, blue);
    }
  }
}

void FractalCreator::calculateRangeTotals() {
  int rangeIndex = 0;
  for (int i = 0; i < mandel::MandelBrot::MAX_ITERATIONS; ++i) {
    int pixel = _histogram[i];

    /* the first element is push from  addColorGradientRange  as 0*/
    if (i >= _itrRange[rangeIndex + 1]) {
      rangeIndex++;
    }
    _totalItrForRange[rangeIndex] += pixel;
  }

  // int overallItr = 0;

  // for (int x : _totalItrForRange) {
  //   overallItr += x;
  //   cout << "Range: " << x << endl;
  // }
  // cout << overallItr << endl;
}

void FractalCreator::writeBitMap(const std::string& name) {
  if (_bitMap.write(name)) {
    cout << "BitMap Created Successully" << endl;
  } else {
    cout << "Failure in writing Bitmap" << endl;
  }
}

void FractalCreator::createFractalImage(const std::string& name) {
  calculateIteration();
  calculateRangeTotals();
  drawFractal();
  writeBitMap(name);
}

}  // namespace Fractal