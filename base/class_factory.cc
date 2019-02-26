// Copyright [year] <Copyright Owner>

#include "base/class_factory.h"

namespace nb {
namespace detail {
namespace {
std::mutex mutex_;
base_factory_map map_;
}  // namespace

std::mutex& get_mutex() { return mutex_; }

class_factory_map& get_class_factory_map(const std::string& base) {
  if (map_.find(base) == map_.end()) {
    map_.emplace(base, class_factory_map());
  }

  return map_[base];
}
}  // namespace detail
}  // namespace nb
