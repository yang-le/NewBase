#include "base/class_factory.h"

NEW_BASE_BEGIN

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

class_factory_map& get_class_factory_map(const std::string& base) {
    auto& base_map = get_base_to_class_factory_map();
    if (base_map.find(base) == base_map.end()) {
        base_map.emplace(base, class_factory_map());
    }

    return base_map[base];
}
} // namespace detail

NEW_BASE_END
