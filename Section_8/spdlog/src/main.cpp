/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <regex>
#include <thread>
// #include <functional>
#include <iostream>

#include "CompressedRotatingSink.h"

using namespace std;

// Logger configuration
static const std::string loggerNameIPU = "ButlerIPU";
static const std::string loggerNameCalibration = "ButlerIPUCalibration";

void setupLogger() {
  const std::string loggerIPUFilePath = "test/ButlerIPUServer.log";
  const std::string loggerCalibFilePath = "test/ButlerIPUCalibration.log";
  std::size_t queue_size = 1048576;
  std::size_t max_file_size = (1024 * 1024 * 100);  // 100 mb
  std::size_t total_files = 5;                      // files to keep
  bool flush_files = false;

  spdlog::init_thread_pool(queue_size, 1);

  auto loggerSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(loggerIPUFilePath, max_file_size, total_files, flush_files);
  loggerSink->set_pattern("[%Y-%d-%m %T.%f] [%l] [%n] [thread %t] %v");
  loggerSink->set_level(spdlog::level::debug);
  auto logger = std::make_shared<spdlog::async_logger>(loggerNameIPU, loggerSink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
  spdlog::register_logger(logger);
  logger->info("Logger Created");
  logger->info("spdlog Version {}.{}.{}", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

  auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  consoleSink->set_level(spdlog::level::debug);

  auto calibrationSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(loggerCalibFilePath, max_file_size, total_files, flush_files);
  calibrationSink->set_level(spdlog::level::debug);

  std::vector<spdlog::sink_ptr> sink_vector{consoleSink, calibrationSink};
  auto loggerCalibration = std::make_shared<spdlog::async_logger>(loggerNameCalibration, sink_vector.begin(), sink_vector.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);

  spdlog::register_logger(loggerCalibration);
  loggerCalibration->info("Logger Created");
  loggerCalibration->info("spdlog Version {}.{}.{}", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
}

void setupCompressedLogger() {
  const std::string loggerIPUFilePath = "test/ButlerIPUServer.log";
  const std::string loggerCalibFilePath = "test/ButlerIPUCalibration.log";
  std::size_t queue_size = 1048576;
  std::size_t max_file_size = (1024  * 5);  // 100 mb
  std::size_t total_files = 2;                    // files to keep
  std::size_t total_comp_files = 5;
  bool flush_files = false;

  spdlog::init_thread_pool(queue_size, 1);

  auto loggerSink = std::make_shared<spdlog::sinks::compressed_rotating_file_sink_mt>(loggerIPUFilePath, max_file_size, total_files, total_comp_files, flush_files);
  loggerSink->set_pattern("[%Y-%d-%m %T.%f] [%l] [%n] [thread %t] %v");
  loggerSink->set_level(spdlog::level::debug);
  auto logger = std::make_shared<spdlog::async_logger>(loggerNameIPU, loggerSink, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
  spdlog::register_logger(logger);
  logger->info("Logger Created");
  logger->info("spdlog Version {}.{}.{}", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);

  auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  consoleSink->set_level(spdlog::level::debug);

  auto calibrationSink = std::make_shared<spdlog::sinks::compressed_rotating_file_sink_mt>(loggerCalibFilePath, max_file_size, total_files, total_comp_files, flush_files);
  calibrationSink->set_level(spdlog::level::debug);

  std::vector<spdlog::sink_ptr> sink_vector{consoleSink, calibrationSink};
  auto loggerCalibration = std::make_shared<spdlog::async_logger>(loggerNameCalibration, sink_vector.begin(), sink_vector.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);

  spdlog::register_logger(loggerCalibration);
  loggerCalibration->info("Logger Created");
  loggerCalibration->info("spdlog Version {}.{}.{}", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
}

int main() {
  // setupLogger();
  setupCompressedLogger();
  auto logger = spdlog::get(loggerNameIPU);
  auto loggerCalib = spdlog::get(loggerNameCalibration);
  uint8_t var = 10;
  loggerCalib->info("Welcome to spdlog {}", var);
  // cout << std::this_thread::get_id() << endl;
  loggerCalib->info("\033[1;4;32mTop Camera Calibration PASS\033[0m");
  loggerCalib->error("\033[1;4;31mTop Camera Calibration FAILED. Calibration value out of bounds\033[0m");

  while (1) {
    logger->info("write Junk");
    usleep(1000);
  }

  return 0;
}
