#include "base/message_bus.h"

NEW_BASE_BEGIN

namespace {
    message_bus bus_;
}

message_bus& get_message_bus() {
    return bus_;
}

NEW_BASE_END
