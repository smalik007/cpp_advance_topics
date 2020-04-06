/*
 * Description - Basic Exception.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <fstream>
#include <iostream>
using namespace std;

int main() {
  cout << "Hello\n";
  const string outFileName = "test.txt";

  // you can define the obj as write only by this
  // ofstream outFileObj;
  // outFileObj.open(outFileName);

  // or read write by this
  fstream outFileObj;
  outFileObj.open(outFileName, ios::out);

  if (outFileObj.is_open()) {
    outFileObj << "Hello there" << endl;
    outFileObj << 123 << endl;
    outFileObj.close();
  } else {
    cout << "Couldn't create file " << outFileName << endl;
  }

  return 0;
}
