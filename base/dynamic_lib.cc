#include "base/dynamic_lib.h"
#include "base/smart_ptr.h"

NEW_BASE_BEGIN

namespace {
std::map<std::string, std::unique_ptr<dynamic_lib>> map_;
}

void load_dynamic_lib(const std::string& path) {
    if (map_.find(path) == map_.end()) {
        map_.emplace(path, utility::make_unique<dynamic_lib>(path));
    }
}

NEW_BASE_END
