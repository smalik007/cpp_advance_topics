/*
 * Description - FractalCreator.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-24 18:06:50
 *
 */

#pragma once

#include <memory>
#include <string>

#include "BitMap.h"
#include "MandelBrot.h"
#include "Zoom.h"
#include "ZoomList.h"

using namespace std;

namespace Fractal {
class FractalCreator {
 private:
  int _width;
  int _height;
  unique_ptr<int[]> _histogram;
  unique_ptr<int[]> _fractal;
  CreateBitMap::BitMap _bitMap;
  zoomList::ZoomList _zoomListObj;

 public:
  FractalCreator(int width, int height);
  ~FractalCreator();

  void calculateIteration(bool zoom);
  void drawFractal();
  void addZoom(const zoom::Zoom& obj);
  void writeBitMap(const std::string& name);
};

}  // namespace Fractal