/*
 * Description - MandelrBrot.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-17 02:29:09
 *
 */

#include "MandelBrot.h"

#include <complex>

using namespace std;

using namespace FractalBitMap;

namespace FractalBitMap {

MandelBrot::MandelBrot(/* args */) {}

MandelBrot::~MandelBrot() {}

int MandelBrot::getIteration(double x, double y) {
  /* The Mandelbrot set is the set of complex numbers c for which the function
    f(z) = z^2 + c  {where z starts from 0, c is any initial complex number or coordinate in x,y plane}
    does not diverge when iterated from z=0, i.e., for which the sequence f(0), f{f(0)}, f(f{f(0)})... etc remains bounded in absolute value. */

  complex<double> z = 0;    // 0 + 0i
  complex<double> c(x, y);  // c = x + iy

  int itr = 0;
  /* More the iteration more the pattern looks good */
  while (itr < MAX_ITERATIONS) {
    /* if z = a + bi
    c = x + iy
    z^2 = a^2 - b^2 + 2abi
    f(z) = real(a^2 - b^2 + x) + i(2ab + y) */
    z = z * z + c;

    /* Set you own infity or the diverge point, since we are going to iterate between -1, 1 range (image scale down to this range) */
    /* abs value give the magnitude of z which the length of the point z from origin.
       abs(z) = sqrt(a^2 + b^2) , where a,b are the real and img component of z*/
    if (abs(z) > 2) {
      break;
    }
    itr++;
  }

  /* The way the mandle brot set work is here we are limiting the range to 2, so any point which has a radius of 2 or greater whill be considered as out of range (on this 2 no is scaled to some large
   * value), So itr start from 0 with a complex no c within -1 to +1 range, and we  see the function takes how much iteration to go beyond 2, so either the iterato will reach 1000 (in that case we
   * color it some color and assume it to be edge of bounded point. While in other case where itr breaks out will be an unbounded point and in that case we mark it as black */

  return itr;
}

}  // namespace FractalBitMap