/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  std::string basename_ = "ButlerIPUServer";
  std::string file_ext_ = ".log";

  std::vector<std::string> compressed_files;
  compressed_files.push_back("ButlerIPUServer.log.10.blabla");
  compressed_files.push_back("ButlerIPUServer.log.7.blabla");
  compressed_files.push_back("ButlerIPUServer.log.1.blabla");
  compressed_files.push_back("ButlerIPUServer.log.5.blabla");
  compressed_files.push_back("ButlerIPUServer.log.2.blabla");
  compressed_files.push_back("ButlerIPUServer.log.3.blabla");
  compressed_files.push_back("ButlerIPUServer.log.6.blabla");
  compressed_files.push_back("ButlerIPUServer.log.4.blabla");

  size_t compare_str_upto = sizeof(basename_) + sizeof(file_ext_) + 2;  // two bytes for . and counter  (basename.ext.counter.timestamp.zst)
  // auto lambda = [compare_str_upto](const char* a, const char* b) { return strncmp(a, b, compare_str_upto); };
  std::sort(compressed_files.begin(), compressed_files.end(), [compare_str_upto](std::string a, std::string b) {
    bool ret = false;
    if (strncmp(a.c_str(), b.c_str(), compare_str_upto) > 0) {
      ret = true;
    }
    return ret;
  });

  cout << endl;
  for (auto file : compressed_files) {
    cout << file << endl;
  }

  cout << endl;

  return 0;
}
