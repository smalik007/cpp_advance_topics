/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>

#include "FractalCreator.h"

using namespace std;

int main() {
  const int WIDTH = 800;
  const int HEIGHT = 600;
  const std::string imageName = "test1.bmp";

  double coordX;
  double coordY;
  double scaleValue;
  bool wantZoom;

  cout << "Zoom (Yes :1, No : 0) :";
  cin >> wantZoom;

  Fractal::FractalCreator fractalCrt(WIDTH, HEIGHT, wantZoom);
  fractalCrt.addColorGradientRange(0.0, rgb::RGB(0, 0, 0));
  fractalCrt.addColorGradientRange(0.3, rgb::RGB(217, 87, 154));
  fractalCrt.addColorGradientRange(0.5, rgb::RGB(0, 0, 0));
  fractalCrt.addColorGradientRange(1.0, rgb::RGB(0, 0, 0));

  cout << fractalCrt.getRangeIndx(450) << endl;

  if (wantZoom) {
    cout << "coordX : ";
    cin >> coordX;
    cout << "coordY : ";
    cin >> coordY;
    cout << "Scale : ";
    cin >> scaleValue;
    fractalCrt.addZoom(zoom::Zoom(coordX, HEIGHT - coordY, scaleValue));
  }

  fractalCrt.createFractalImage(imageName);

  return 0;
}
