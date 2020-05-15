/*
 * Description - CompressedRotatingSink.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-05-05 02:26:03
 *
 */
#ifndef COMPRESSED_ROTATING_SINK_H
#define COMPRESSED_ROTATING_SINK_H

#include <spdlog/details/file_helper.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/details/synchronous_factory.h>
#include <spdlog/sinks/base_sink.h>

#include <algorithm>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <regex>
#include <string>
using namespace boost::filesystem;
using namespace std;

namespace Utility {
static std::string getTime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) - std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

  std::ostringstream timeStr;

  // TODO: Flaw in char implementation size fixed. Upgrade compiler to gcc > 5
  char timeChar[100];
  std::strftime(timeChar, sizeof(timeChar), "%d_%b_%EY_%H_%M_%S_", std::localtime(&time));
  timeStr << timeChar;
  // timeStr << std::put_time(std::localtime(&time), "%d_%b_%EY_%H:%M:%S:");
  timeStr << ms.count();

  return timeStr.str();
}
}  // namespace Utility

namespace spdlog {
namespace sinks {

//
// Rotating file sink based on size
//
template <typename Mutex>
class compressed_rotating_file_sink final : public base_sink<Mutex> {
 public:
  compressed_rotating_file_sink(filename_t base_filename, std::size_t max_size, std::size_t max_files, std::size_t max_comp_files, bool rotate_on_open = false);
  static filename_t calc_filename(const filename_t& filename, std::size_t index);
  const filename_t& filename() const;

 protected:
  void sink_it_(const details::log_msg& msg) override;
  void flush_() override;

 private:
  // Rotate files:
  // log.txt -> log.1.txt
  // log.1.txt -> log.2.txt
  // log.2.txt -> log.3.txt
  // log.3.txt -> delete
  void rotate_();
  void compress_();

  // delete the target if exists, and rename the src file  to target
  // return true on success, false otherwise.
  bool rename_file(const filename_t& src_filename, const filename_t& target_filename);

  filename_t base_filename_;
  std::size_t max_size_;
  std::size_t max_files_;
  std::size_t max_compressed_files_;
  std::size_t current_size_;
  details::file_helper file_helper_;
  path dir_;
  filename_t basename_;
  filename_t file_ext_;
};

using compressed_rotating_file_sink_mt = compressed_rotating_file_sink<std::mutex>;
using compressed_rotating_file_sink_st = compressed_rotating_file_sink<details::null_mutex>;

template <typename Mutex>
SPDLOG_INLINE compressed_rotating_file_sink<Mutex>::compressed_rotating_file_sink(filename_t base_filename, std::size_t max_size, std::size_t max_files, std::size_t max_comp_files,
                                                                                  bool rotate_on_open)
    : base_filename_(std::move(base_filename)), max_size_(max_size), max_files_(max_files), max_compressed_files_(max_comp_files) {
  file_helper_.open(calc_filename(base_filename_, 0));
  current_size_ = file_helper_.size();  // expensive. called only once
  path p(base_filename_);
  dir_ = p.parent_path();
  filename_t file_name = p.filename().string();
  std::tie(basename_, file_ext_) = details::file_helper::split_by_extension(file_name);
  if (rotate_on_open && current_size_ > 0) {
    rotate_();
    compress_();
  }
}

// calc filename according to index and file extension if exists.
// e.g. calc_filename("logs/mylog.txt, 3) => "logs/mylog.3.txt".
template <typename Mutex>
SPDLOG_INLINE filename_t compressed_rotating_file_sink<Mutex>::calc_filename(const filename_t& filename, std::size_t index) {
  if (index == 0u) {
    return filename;
  }

  filename_t basename, ext;
  std::tie(basename, ext) = details::file_helper::split_by_extension(filename);
  return fmt::format(SPDLOG_FILENAME_T("{}.{}{}"), basename, index, ext);
}

template <typename Mutex>
SPDLOG_INLINE const filename_t& compressed_rotating_file_sink<Mutex>::filename() const {
  return file_helper_.filename();
}

template <typename Mutex>
SPDLOG_INLINE void compressed_rotating_file_sink<Mutex>::sink_it_(const details::log_msg& msg) {
  memory_buf_t formatted;
  base_sink<Mutex>::formatter_->format(msg, formatted);
  current_size_ += formatted.size();
  if (current_size_ > max_size_) {
    rotate_();
    compress_();
    current_size_ = formatted.size();
  }
  file_helper_.write(formatted);
}

template <typename Mutex>
SPDLOG_INLINE void compressed_rotating_file_sink<Mutex>::flush_() {
  file_helper_.flush();
}

// Rotate files:
// log.txt -> log.1.txt
// log.1.txt -> log.2.txt
// log.2.txt -> log.3.txt
// log.3.txt -> delete
template <typename Mutex>
SPDLOG_INLINE void compressed_rotating_file_sink<Mutex>::rotate_() {
  using details::os::filename_to_str;
  using details::os::path_exists;
  file_helper_.close();
  for (auto i = max_files_; i > 0; --i) {
    filename_t src = calc_filename(base_filename_, i - 1);
    if (!path_exists(src)) {
      continue;
    }
    filename_t target = calc_filename(base_filename_, i);

    if (!rename_file(src, target)) {
      // if failed try again after a small delay.
      // this is a workaround to a windows issue, where very high rotation
      // rates can cause the rename to fail with permission denied (because of antivirus?).
      details::os::sleep_for_millis(100);
      if (!rename_file(src, target)) {
        file_helper_.reopen(true);  // truncate the log file anyway to prevent it to grow beyond its limit!
        current_size_ = 0;
        SPDLOG_THROW(spdlog_ex("rotating_file_sink: failed renaming " + filename_to_str(src) + " to " + filename_to_str(target), errno));
      }
    }
  }
  file_helper_.reopen(true);
}

// delete the target if exists, and rename the src file  to target
// return true on success, false otherwise.
template <typename Mutex>
SPDLOG_INLINE bool compressed_rotating_file_sink<Mutex>::rename_file(const filename_t& src_filename, const filename_t& target_filename) {
  // try to delete the target file in case it already exists.
  (void)details::os::remove(target_filename);
  return details::os::rename(src_filename, target_filename) == 0;
}

template <typename Mutex>
SPDLOG_INLINE void compressed_rotating_file_sink<Mutex>::compress_() {
  using details::os::filename_to_str;
  using details::os::path_exists;
  const std::string comp_ext = ".gz";
  std::string basename_local;
  path dir_local = dir_;
  if (dir_local.string().empty()) {
    dir_local = "./";
    basename_local = "./" + basename_;
  } else {
    basename_local = dir_local.string() + "/" + basename_;
  }

  cout << "compress_" << std::endl;
  cout << "basename_local : " << basename_local << std::endl;
  std::size_t max_itr_value = (max_compressed_files_ + max_files_ - 1);
  std::size_t i = max_itr_value;
  for (; i >= max_files_; --i) {
    if (i == max_files_) {
      filename_t src = calc_filename(base_filename_, i);
      if (!path_exists(src)) {
        continue;
      }
      auto timeNow = std::chrono::high_resolution_clock::now();
      std::string compressed_file_name;
      compressed_file_name = src + "." + Utility::getTime() + comp_ext;
      // std::string command_str = "tar czfP " + compressed_file_name + " " + src;
      // system(command_str.c_str());

      std::ifstream file(src, ios_base::binary);
      //      boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
      //      in.push(boost::iostreams::basic_zlib_compressor());
      //      in.push(file);

      boost::iostreams::file_sink ofile(compressed_file_name);
      boost::iostreams::filtering_streambuf<boost::iostreams::output> out;
      out.set_auto_close(true);

      out.push(boost::iostreams::gzip_compressor());
      out.push(ofile);
      //      std::cout << "out.is_complete(): " << out.is_complete() << endl;
      //      std::cout << "ifs.is_open()? "     << file.is_open()     << endl;
      //      std::cout << "ofile.is_open()? "   << ofile.is_open()   << endl;
      //

      boost::iostreams::copy(file, out);

      // std::cout << "out.is_complete(): " << out.is_complete() << endl;
      // std::cout << "ifs.is_open()? " << file.is_open() << endl;
      // std::cout << "ofile.is_open()? " << ofile.is_open() << endl;

      details::os::remove(src);
      double diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeNow).count();
      std::cout << "time taken to compress : " << diff << std::endl;
    }

    if (i > max_files_) {
      try {
        if (exists(dir_local)) {
          cout << dir_local << " is a directory containing:\n";
          std::string regix_str = basename_local + "." + std::to_string(i - 1) + file_ext_ + "(.*)" + comp_ext;
          std::string regix_oldest_str = basename_local + "." + std::to_string(i) + file_ext_ + "(.*)" + comp_ext;
          std::string format_to_replace = "." + std::to_string(i - 1);
          std::string replace_str = "." + std::to_string(i);
          for (auto x : directory_iterator(dir_local)) {
            filename_t src_name = x.path().string();
            filename_t target_name = src_name;

            if (i == max_itr_value) {
              if (std::regex_match(src_name, std::regex(regix_oldest_str))) {
                cout << "Oldest file deleting: " << src_name << std::endl;
                details::os::remove(src_name);
              }
            }

            if (std::regex_match(src_name, std::regex(regix_str))) {
              cout << "Matched file is :" << x.path() << std::endl;
              boost::algorithm::replace_first(target_name, format_to_replace, replace_str);
              cout << "Renaming file  " << src_name << " to " << target_name << std::endl;
              if (!rename_file(src_name, target_name)) {
                // if failed try again after a small delay.
                // this is a workaround to a windows issue, where very high rotation
                // rates can cause the rename to fail with permission denied (because of antivirus?).
                details::os::sleep_for_millis(100);
                if (!rename_file(src_name, target_name)) {
                  SPDLOG_THROW(spdlog_ex("rotating_file_sink: failed renaming " + filename_to_str(src_name) + " to " + filename_to_str(target_name), errno));
                }
              }
            }
          }
        }

      } catch (const filesystem_error& ex) {
        cout << ex.what() << '\n';
      }
    }
  }
}
}  // namespace sinks
}  // namespace spdlog

#endif