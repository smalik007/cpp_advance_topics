/*
 * Description - MandelBrot.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-17 02:28:08
 *
 */

#ifndef MANDEL_BROT_H
#define MANDEL_BROT_H

namespace FractalBitMap {

class MandelBrot {
 public:
  static const int MAX_ITERATIONS = 1000; /* more the iteration the better the quality of image, have to trade off btw quality vs time */

 public:
  MandelBrot(/* args */);
  ~MandelBrot();
  static int getIteration(double x, double y);
};
}  // namespace FractalBitMap

#endif
