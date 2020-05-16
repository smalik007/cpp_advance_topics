/*
 * Description - BitMap.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-17 00:33:27
 *
 */

#include "BitMap.h"

#include <fstream>

#include "BitMapFile.h"
#include "BitMapInfo.h"

using namespace FactralBitMap;
using namespace std;

namespace FactralBitMap {
BitMap::BitMap(int width, int height) : _width(width), _height(height), _pPixel(new uint8_t[width * height * COLOR_CHANNELS]{}) {}

bool BitMap::write(string filename) {
  BitMapFile fileHeader;
  BitMapInfo infoHeader;

  fileHeader.fileSize = sizeof(BitMapFile) + sizeof(BitMapInfo) + (_width * _height * COLOR_CHANNELS);
  fileHeader.dataOffset = sizeof(BitMapFile) + sizeof(BitMapInfo); /* After this info info is where the actual data start */

  infoHeader.width = _width;
  infoHeader.height = _height;

  ofstream file;
  file.open(filename, ios::out | ios::binary);

  if (!file) {
    return false;
  }

  file.write((char*)&fileHeader, sizeof(fileHeader));
  file.write((char*)&infoHeader, sizeof(infoHeader));
  file.write((char*)_pPixel.get(), (_width * _height * COLOR_CHANNELS));

  file.close();

  if (!file) {
    return false;
  }

  return true;
}

void BitMap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t* pPixel = _pPixel.get();

  /*  (0,0) -----------------------------> width (x) */
  /*        -                                        */
  /*        -                                        */
  /*        -                                        */
  /*        -                                        */
  /*        -               (x, y)                   */
  /*        -                                        */
  /*        -                                        */
  /*    (y) -                                        */
  /*   height                                        */
  /*                                                 */

  /* To get to (x, y) , also remember we have 3 bytes (RGB) per pixel*/
  pPixel += ((y * COLOR_CHANNELS) * _width) + (x * COLOR_CHANNELS);

  /* bitMap is a little-endian format hence the colors order would be filled in reverse order  */
  pPixel[0] = blue;
  pPixel[1] = green;
  pPixel[2] = red;
}

BitMap::~BitMap() {}
}  // namespace FactralBitMap
