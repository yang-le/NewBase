#pragma once

#include <sstream>
#include "base/macros.h"
#include "external/spdlog/spdlog.h"

NEW_BASE_BEGIN

namespace log {
template <spdlog::level::level_enum level>
struct spdlogger {
public:
    spdlogger() : logger_(spdlog::default_logger_raw()) { }

    spdlogger(const spdlog::logger* logger) : logger_(logger) { }

    ~spdlogger() {
        if (logger_->should_log(level)) {
            logger_->log(level, stream_.str());
        }
    }

    std::ostringstream &stream() {
        return stream_;
    }

private:
    spdlog::logger* logger_;
    std::ostringstream stream_;
};
}

NEW_BASE_END

#define LOG_E log::spdlogger<spdlog::level::err>().stream()
#define LOG_W log::spdlogger<spdlog::level::warn>().stream()
#define LOG_I log::spdlogger<spdlog::level::info>().stream()
