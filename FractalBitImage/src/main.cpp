/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <algorithm>
#include <iostream>

#include "BitMap.h"

using namespace std;

int main() {
  const int WIDTH = 800;
  const int HEIGHT = 600;
  FactralBitMap::BitMap bitMap(WIDTH, HEIGHT);

  // bitMap.setPixel(WIDTH / 2, HEIGHT / 2, 255, 255, 255);

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) bitMap.setPixel(x, y, 255, 0, 0);
  }

  if (bitMap.write("test.bmp")) {
    cout << "BitMap Created Successully" << endl;
  } else {
    cout << "Failure in writing Bitmap" << endl;
  }

  return 0;
}
