/*
 * Description - BitMapInfo.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-16 23:49:36
 *
 */

#ifndef BITMAPINFO_H
#define BITMAPINFO_H

#include <cstdint> /* for int32_t */

using namespace std;

namespace CreateBitMap {
#pragma pack(2)
struct BitMapInfo {
  int32_t headerSize{40};
  int32_t width;
  int32_t height;
  int16_t planes{1};
  int16_t bitsPerPixel{24}; /* 1 byte for each color RGB (8 * 3) -> 24 bytes */
  int32_t compression{0};
  int32_t dataSize{0};
  int32_t horizontalResolution{2400};
  int32_t verticalResolution{2400};
  int32_t colors{0};
  int32_t importantColors{0};
};
}  // namespace CreateBitMap

#endif /* BITMAPINFO_H */