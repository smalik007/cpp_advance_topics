/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <archive.h>
#include <archive_entry.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <cstdlib>

#include <boost/asio.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

using namespace std;

void write_archive(const char* outname, std::vector<std::string> files) {
  struct archive* a;
  struct archive_entry* entry;
  struct stat st;
  char buff[8192];
  int len;
  int fd;

  a = archive_write_new();
  archive_write_add_filter_gzip(a);
  archive_write_set_format_pax_restricted(a);  // Note 1
  archive_write_open_filename(a, outname);
  entry = archive_entry_new();  // Note 2
  for(size_t i = 0; i < files.size(); i++){
    stat(files[i].c_str(), &st);
    // std::cout << "filename : " << files[i] << std::endl;
    archive_entry_set_pathname(entry, files[i].c_str());
    archive_entry_set_size(entry, st.st_size);  // Note 3
    archive_entry_set_filetype(entry, AE_IFREG);
    archive_entry_set_perm(entry, 0644);
    archive_write_header(a, entry);
    fd = open(files[i].c_str(), O_RDONLY);
    len = read(fd, buff, sizeof(buff));
    while (len > 0) {
      archive_write_data(a, buff, len);
      len = read(fd, buff, sizeof(buff));
    }
    close(fd);
    archive_entry_clear(entry);
  }
  archive_entry_free(entry);
  archive_write_close(a);  // Note 4
  archive_write_free(a);   // Note 5
}

int main() {
  const char* outname;
  outname = "/home/suhail/bc_image/top_50.tar.gz";
  const std::string compressed_file_name = "/home/suhail/bc_image/top_50.tar.gz";

  boost::filesystem::path dir("/home/suhail/bc_image/top_50");

  std::vector<std::string> files;
  for (auto x : boost::filesystem::directory_iterator(dir)) {
    std::ifstream file(x.path().string(), ios_base::in);
    // std::cout << "filename : " << x.path().string() << std::endl;
    files.push_back(x.path().string());
  }

  auto timeNow = std::chrono::high_resolution_clock::now();
  write_archive(outname, files);
  double diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeNow).count();
  std::cout << "time taken to compress : " << diff << std::endl;

  // auto timeNow = std::chrono::high_resolution_clock::now();
  // std::string command_str = "tar czfP " + compressed_file_name + " " + dir.string();
  // system(command_str.c_str());
  // double diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeNow).count();
  // std::cout << "time taken to compress : " << diff << std::endl;

  return 0;
}
