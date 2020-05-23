/*
 * Description - zoomList.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-24 02:45:49
 *
 */

#include "ZoomList.h"

#include <iostream>

namespace zoomList {
ZoomList::ZoomList(int width, int height) : _width(width), _height(height) {}

void ZoomList::add(const zoom::Zoom& obj) {
  zoomsVector.push_back(obj);
  _xCenter = (obj.x - _width / 2) * _scale;
  _yCenter = (obj.y - _height / 2) * _scale;

  /* new Scale */
  _scale *= obj.scale;

  std::cout << "xCenter : " << _xCenter << ", yCenter : " << _yCenter << ", scale : " << _scale << std::endl;
}

std::pair<double, double> ZoomList::doZoom(int x, int y) { return std::pair<double, double>(0.0, 0.0); }

}  // namespace zoomList