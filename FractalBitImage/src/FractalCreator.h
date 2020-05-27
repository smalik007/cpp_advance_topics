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
#include <vector>

#include "BitMap.h"
#include "MandelBrot.h"
#include "RGB.h"
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
  bool _zoomFalg;
  std::vector<int> _itrRange;
  std::vector<rgb::RGB> _colorRange;
  std::vector<int> _totalItrForRange;

  bool _itrInit{false};

 private:
  void calculateIteration();
  void drawFractal();
  void writeBitMap(const std::string& name);
  void calculateRangeTotals();

 public:
  FractalCreator() = delete;
  FractalCreator(int width, int height, bool zoom);
  ~FractalCreator();

  void addZoom(const zoom::Zoom& obj);
  void createFractalImage(const std::string& name);
  void addColorGradientRange(double itrRange, const rgb::RGB& color);
};

}  // namespace Fractal