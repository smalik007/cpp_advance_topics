/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>

#include "FractalCreator.h"
#include "RGB.h"

using namespace std;

int main() {
  const int WIDTH = 800;
  const int HEIGHT = 600;
  const std::string imageName = "test1.bmp";
  Fractal::FractalCreator fractalCrt(WIDTH, HEIGHT);

  double coordX;
  double coordY;
  double scaleValue;
  bool wantZoom;

  cout << "Zoom (Yes :1, No : 0) :";
  cin >> wantZoom;

  if (wantZoom) {
    cout << "coordX : ";
    cin >> coordX;
    cout << "coordY : ";
    cin >> coordY;
    cout << "Scale : ";
    cin >> scaleValue;
    fractalCrt.addZoom(zoom::Zoom(coordX, HEIGHT - coordY, scaleValue));
  }
  fractalCrt.calculateIteration(wantZoom);
  fractalCrt.drawFractal();
  fractalCrt.writeBitMap(imageName);

  return 0;
}
