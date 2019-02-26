// Copyright [year] <Copyright Owner>

#pragma once

#include <sstream>
#if 0
#include "external/spdlog/spdlog.h"

namespace nb {

namespace log {
template <spdlog::level::level_enum level>
class spdlogger {
 public:
  explicit spdlogger(spdlog::source_loc loc)
      : loc_(loc), logger_(spdlog::default_logger_raw()) {}

  spdlogger(spdlog::source_loc loc, spdlog::logger* logger)
      : loc_(loc), logger_(logger) {}

  ~spdlogger() {
    if (logger_->should_log(level)) {
      logger_->log(loc_, level, stream_.str());
    }
  }

  std::ostringstream& stream() { return stream_; }

 private:
  spdlog::source_loc loc_;
  spdlog::logger* logger_;
  std::ostringstream stream_;
};
}  // namespace log

}  // namespace nb

#define LOG_E                                                      \
  nb::log::spdlogger<spdlog::level::err>(                          \
      spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, \
                         SPDLOG_FUNCTION})                         \
      .stream()
#define LOG_W                                                      \
  nb::log::spdlogger<spdlog::level::warn>(                         \
      spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, \
                         SPDLOG_FUNCTION})                         \
      .stream()
#define LOG_I                                                      \
  nb::log::spdlogger<spdlog::level::info>(                         \
      spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, \
                         SPDLOG_FUNCTION})                         \
      .stream()
#else
#include <iostream>
#define LOG_E std::cerr
#define LOG_W std::cerr
#define LOG_I std::cout
#endif
