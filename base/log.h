// Copyright [year] <Copyright Owner>

#pragma once

#include <sstream>
#include "base/macros.h"
#include "external/spdlog/spdlog.h"

NEW_BASE_BEGIN

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

NEW_BASE_END

#define LOG_E                                                      \
  NEW_BASE::log::spdlogger<spdlog::level::err>(                    \
      spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, \
                         SPDLOG_FUNCTION})                         \
      .stream()
#define LOG_W                                                      \
  NEW_BASE::log::spdlogger<spdlog::level::warn>(                   \
      spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, \
                         SPDLOG_FUNCTION})                         \
      .stream()
#define LOG_I                                                      \
  NEW_BASE::log::spdlogger<spdlog::level::info>(                   \
      spdlog::source_loc{SPDLOG_FILE_BASENAME(__FILE__), __LINE__, \
                         SPDLOG_FUNCTION})                         \
      .stream()
