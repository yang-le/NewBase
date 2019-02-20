#include "base/dynamic_lib.h"

NEW_BASE_BEGIN

namespace detail {
namespace {
dynamic_lib_map map_;
} // namepsace <unnamed>

dynamic_lib_map& get_dynamic_lib_map() {
    return map_;
}
} // namespace detail

void load_dynamic_lib(const std::string& path) {
    auto& map = detail::get_dynamic_lib_map();
    if (map.find(path) == map.end()) {
        map.emplace(path, std::make_unique<dynamic_lib>(path));
    }
}

NEW_BASE_END
