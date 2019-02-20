#pragma once

#include <string.h>
#include "base/macros.h"

NEW_BASE_BEGIN

namespace platform {

enum state : std::uint8_t {
    STATE_UNINITIALIZED = 0,
    STATE_INITIALIZED,
    STATE_SHUTTING_DOWN,
    STATE_SHUTDOWN,
};

NEW_BASE_API bool run(const std::string& config_file);
}

NEW_BASE_END
