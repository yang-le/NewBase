#include "base/dynamic_lib.h"

namespace detail {
namespace {
    dynamic_lib_map map;
} // namepsace <unnamed>

dynamic_lib_map& get_dynamic_lib_map() {
    return map;
}
} // namespace detail
