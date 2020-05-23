/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <archive.h>
#include <archive_entry.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

#include <boost/asio.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <chrono>
// #include <cstdlib>
#include <common.h>  // Helper functions, CHECK(), and CHECK_ZSTD()
#include <stdio.h>   // printf
#include <string.h>  // strlen, strcat, memset
#include <zstd.h>    // presumes zstd library is installed

#include <iostream>

using namespace std;

namespace zstd {

static const std::string extFile = ".zst";
static const std::string archiveExt = ".tar.zst";

class Compressor {
 public:
  static bool ArchiveDir(const std::string outname, const std::string directoryName) {
    // const std::string archiveExt = ".tar.zst";
    struct archive* a;
    struct archive_entry* entry;
    struct stat st;
    char buff[8192];
    int len;
    int fd;

    std::stringstream outputFile;
    outputFile << outname << archiveExt;
    std::vector<std::string> files;

    try {
      boost::filesystem::path dir(directoryName);
      for (auto x : boost::filesystem::directory_iterator(dir)) {
        std::ifstream file(x.path().string(), ios_base::in);
        files.push_back(x.path().string());
      }
    } catch (const boost::filesystem::filesystem_error& err) {
      cout << "Problem in boost" << endl;
      return false;
    }

    a = archive_write_new();
    archive_write_add_filter_zstd(a);
    archive_write_set_format_pax_restricted(a);
    archive_write_open_filename(a, outputFile.str().c_str());
    entry = archive_entry_new();
    for (size_t i = 0; i < files.size(); i++) {
      stat(files[i].c_str(), &st);
      archive_entry_set_pathname(entry, files[i].c_str());
      archive_entry_set_size(entry, st.st_size);
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
    archive_write_close(a);
    archive_write_free(a);

    return true;
  }

  static bool CompressFile(const std::string outname, const std::string filePath) {
    // const std::string extFile = ".zst";
    std::stringstream outputFile;
    outputFile << outname << extFile;
    size_t fSize;
    void* const fBuff = mallocAndLoadFile_orDie(filePath.c_str(), &fSize);
    size_t const cBuffSize = ZSTD_compressBound(fSize);
    void* const cBuff = malloc_orDie(cBuffSize);

    size_t const cSize = ZSTD_compress(cBuff, cBuffSize, fBuff, fSize, 1);
    CHECK_ZSTD(cSize);

    saveFile_orDie(outputFile.str().c_str(), cBuff, cSize);

    free(fBuff);
    free(cBuff);
    return true;
  }
};
}  // namespace zstd

int main() {
  // const std::string outname = "/home/suhail/bc_image/top_50_some_var";
  // const std::string direct = "/home/suhail/bc_image/top_50";
  const std::string fileOut = "/home/suhail/bc_image/test_log_something.log";
  const std::string filName = "/home/suhail/bc_image/test_log.log";

  const std::string outname = "/home/suhail/bc_image/log_some_var";
  const std::string direct = "/home/suhail/bc_image/log";
  ;

  cout << zstd::extFile << endl;

  auto timeNow = std::chrono::high_resolution_clock::now();
  zstd::Compressor::ArchiveDir(outname, direct);
  double diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeNow).count();
  std::cout << "time taken to compress : " << diff << std::endl;

  timeNow = std::chrono::high_resolution_clock::now();
  zstd::Compressor::CompressFile(fileOut, filName);
  diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeNow).count();
  std::cout << "time taken to compress : " << diff << std::endl;

  return 0;
}
