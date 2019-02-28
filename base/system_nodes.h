// Copyright [year] <Copyright Owner>

#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <vector>
#include <string>
#include "base/macros.h"
#include "base/node.h"

namespace nb {
namespace system_nodes {
class registry {
 public:
  template <typename T>
  struct register_handler {
    template <typename... Args>
    explicit register_handler(Args &&... args) {
      registry::instance().funcs_.emplace_back([=] {
        std::unique_ptr<node_base> node = std::make_unique<T>();
        if (!node->init(args...)) {
          throw std::runtime_error(std::string("cannot init system node: ") +
                                   typeid(T).name());
        }
        registry::instance().nodes_.emplace_back(std::move(node));
      });
    }
  };

  void start_all() {
    std::call_once(once_flag_, [this] {
      for (auto f : funcs_) {
        f();
      }
    });
  }

 private:
  std::vector<std::function<void()>> funcs_;
  std::vector<std::unique_ptr<node_base>> nodes_;
  std::once_flag once_flag_;

  DECLARE_SINGLETON(registry);
};

void start_all();
}  // namespace system_nodes
}  // namespace nb

#define SYSTEM_NODE_REGIST(n, ...)                                           \
  using nb::system_node::##n;                                                \
  namespace {                                                                \
  nb::system_nodes::registry::register_handler<n> handler_(##__VA_ARGS__);   \
  }
