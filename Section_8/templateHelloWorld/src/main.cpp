#include <algorithm>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <regex>
#include <vector>
using std::cout;
using namespace boost::filesystem;

int main(int argc, char* argv[]) {
  // if (argc < 2) {
  //   cout << "Usage: tut4 path\n";
  //   return 1;
  // }

  std::string base_filename_ = "/data/fw/log/ipu/ButlerIPUServer.log";
  path p(base_filename_);
  path dir = p.parent_path();

  std::string name_file = "/data/fw/log/ipu/ButlerIPUServer";
  std::string ext = ".log";

  int i = 2;

  try {
    if (exists(dir)) {
      if (is_directory(dir)) {
        cout << dir << " is a directory containing:\n";
        std::string regix_str = name_file + "." + std::to_string(i - 1) + ext + "(.*)(.tar.gz)";
        std::string format_to_replace = "." + std::to_string(i - 1);
        std::string replace_str = "." + std::to_string(i);
        for (auto x : directory_iterator(dir)) {
          std::string filen = x.path().string();
          std::string file_rename = filen;
          if (std::regex_match(filen, std::regex(regix_str))) {
            cout << "Matched file is :" << x.path() << std::endl;
            boost::algorithm::replace_first(file_rename, format_to_replace, replace_str);
            cout << "Renaming file to : " << file_rename << std::endl;
          }
        }
      } else
        cout << p << " exists, but is not a regular file or directory\n";
    } else
      cout << p << " does not exist\n";
  }

  catch (const filesystem_error& ex) {
    cout << ex.what() << '\n';
  }

  return 0;
}