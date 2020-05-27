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

namespace mandel {

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

  return itr;
}

}  // namespace mandel