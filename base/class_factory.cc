#include "base/class_factory.h"

NEW_BASE_BEGIN

namespace detail {
namespace {
    std::mutex mutex_;
    base_factory_map map_;
} // namepsace <unnamed>

std::mutex& get_mutex() {
    return mutex_;
}

class_factory_map& get_class_factory_map(const std::string& base) {
    if (map_.find(base) == map_.end()) {
        map_.emplace(base, class_factory_map());
    }

    return map_[base];
}
} // namespace detail

NEW_BASE_END
