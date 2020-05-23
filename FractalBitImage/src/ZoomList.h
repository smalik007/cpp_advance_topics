/*
 * Description - ZoomList.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-24 02:42:39
 *
 */

#pragma once

#include <utility>
#include <vector>

#include "Zoom.h"

namespace zoomList {
class ZoomList {
 private:
  int _width{0};
  int _height{0};
  std::vector<zoom::Zoom> zoomsVector;
  double _xCenter{0.0};
  double _yCenter{0.0};
  double _scale{1.0};

 public:
  ZoomList(int width, int height);
  void add(const zoom::Zoom& obj);
  std::pair<double, double> doZoom(int x, int y);
};

}  // namespace zoomList