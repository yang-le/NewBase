// Copyright [year] <Copyright Owner>

#include "base/message_bus.h"

namespace nb {

DEFINE_SINGLETON(message_bus);

message_bus::message_bus() = default;
message_bus::~message_bus() = default;

}
