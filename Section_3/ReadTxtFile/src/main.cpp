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
  cout << "Hello\n";
  const string fileName = "test.txt";

  // ifstream inFile;
  // inFile.open(fileName);

  // or you can use this
  fstream inFile;
  inFile.open(fileName, ios::in);

  if (inFile.is_open()) {
    string word;
    string line;

    // inFile >> word;
    // cout << word << endl;

    // while(inFile) would also be sufficient, as passing this ensure it handle the read till end of file.
    while (!inFile.eof()) {
      getline(inFile, line);
      cout << line << endl;
    }

    inFile.close();
  } else {
    cout << "Couldn't open file " << fileName << endl;
  }

  return 0;
}
