#include "base/message_bus.h"

NEW_BASE_BEGIN

DEFINE_SINGLETON(message_bus);

message_bus::message_bus() = default;
message_bus::~message_bus() = default;

NEW_BASE_END
