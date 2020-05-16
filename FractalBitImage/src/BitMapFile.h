/*
 * Description - BitMapFile.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-16 23:49:36
 *
 */

/* The significance for defining this as preprocessor macro is that, before the compiler starts compiling the code, preprocessor, check in multiple file and the nested hierarchy of includes and
 * prevents inclusion of this header file again and again if some other files has already included it. If this these statement are missing from your header file, you might endup including the same
 * headerfiles again and again and your total compilation size will increase */
#ifndef BITMAPFILE_H
#define BITMAPFILE_H

#include <cstdint> /* for int32_t */

using namespace std;

namespace CreateBitMap {
#pragma pack(2)
struct BitMapFile {
  char header[2]{'B', 'M'}; /* since it's just 2 bytes, compiler would add a padding of 2 bytes between this and the next element , to avoid padding added pragma pack(n) n could be {1, 2, 4, 8}*/
  int32_t fileSize;         /* Need to make sure 32bit int */
  int32_t reserved{0};
  int32_t dataOffset;
};
}  // namespace CreateBitMap

#endif /* BITMAPFILE_H */
