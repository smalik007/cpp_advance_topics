/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <fstream>
#include <iostream>
using namespace std;

#pragma pack(push, 1)
/* Structure uses padding to fill the empty space, here in the below case the actual combine size of the variables is only
  50 + 4 (int) + 8 (double) = 62 bytes, but the structure Size would be 64, to remove this extra padding we can use preprocessor
  padding #pragma pack(), and pop surrounded to the structure. This is perticularly helpul while you are using to parse data and
  using pointer to the structre and accessing bytes by index
 */
struct Person {
  char name[50];
  int age;
  double height;
};

#pragma pack(pop)

int main() {
  Person personObj = {"Frodo", 220, 0.8};
  // cout << sizeof(Person) << endl;
  const string fileName = "test.bin";
  ofstream outFile;
  outFile.open(fileName, ios::binary);

  if (!outFile.is_open()) {
    cout << "Couldn't Create the file " << fileName << endl;
    return 1;
  }

  outFile.write(reinterpret_cast<char*>(&personObj), sizeof(Person));
  outFile.close();

  ///////////////////////////////////////////////////////////////////
  // Reading Binary File

  ifstream inputFile;

  inputFile.open(fileName, ios::binary);

  if (!inputFile.is_open()) {
    cout << "Couldn't open file " << fileName << endl;
    return 1;
  }

  Person readFromFile = {};

  inputFile.read(reinterpret_cast<char*>(&readFromFile), sizeof(Person));

  cout << readFromFile.name << " is " << readFromFile.age << " years old and has " << readFromFile.height << "m height." << endl;

  inputFile.close();

  return 0;
}
