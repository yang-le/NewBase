// Copyright [year] <Copyright Owner>

#pragma once

#include <memory>
#include <utility>  // for std::forward

namespace nb {

// the c++14 make_unique

namespace utility {
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}  // namespace utility

}  // namespace nb
