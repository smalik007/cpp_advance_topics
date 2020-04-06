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

int main() {
  // cout << "Hello\n";
  const string fileName = "test.txt";
  ifstream inputFile;
  inputFile.open(fileName);

  if (!inputFile.is_open()) {
    cout << "Couldn't Open file " << fileName << endl;
    return 1;
  }

  while (inputFile) {
    string line;
    int population;
    getline(inputFile, line, ':');
    inputFile >> population;

    // to get rid of end of line character, discard this byte
    // inputFile.get();

    // in c++ 11 we can use ws (white space to get it discard more efficient way)
    inputFile >> ws;

    if (!inputFile) {
      break;
    }

    cout << line << "--" << population << endl;
  }

  inputFile.close();

  return 0;
}
