// Copyright [year] <Copyright Owner>

#include "base/system_nodes.h"

namespace nb {
namespace system_nodes {
DEFINE_SINGLETON(registry);

registry::registry() = default;
registry::~registry() = default;

void start_all() { registry::instance().start_all(); }
}
}
