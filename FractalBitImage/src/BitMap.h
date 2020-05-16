/*
 * Description - BitMap.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-16 23:49:36
 *
 */

#ifndef BITMAP_H
#define BITMAP_H

#include <cstdint>
#include <memory>
#include <string>

using namespace std;

#define COLOR_CHANNELS 3

namespace CreateBitMap {
class BitMap {
 private:
  int _width{0};
  int _height{0};
  unique_ptr<uint8_t[]> _pPixel{nullptr};

 public:
  BitMap(int width, int height);
  bool write(string filename);
  void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
  ~BitMap();
};

}  // namespace CreateBitMap

#endif /* BITMAP_H */