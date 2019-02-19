#include "base/class_factory.h"

namespace detail {
namespace {
    std::mutex m;
    base_factory_map map;
} // namepsace <unnamed>

std::mutex& get_mutex() {
    return m;
}

base_factory_map& get_base_to_class_factory_map() {
    return map;
}
} // namespace detail
