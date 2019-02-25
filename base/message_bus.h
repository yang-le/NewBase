// Copyright [year] <Copyright Owner>

#pragma once

#include <functional>
#include <mutex>
#include <string>
#include <tuple>
#include <utility>
#include <unordered_map>
#include "base/function_traits.h"
#include "base/integer_sequence.h"
#include "base/macros.h"

NEW_BASE_BEGIN

class message_bus {
 public:
  template <typename F>
  void subscribe(const std::string& topic, const F& f) {
    std::lock_guard<std::mutex> lock(mutex_);
    map_.emplace(topic,
                 std::bind(&invoker<F>::apply, f, std::placeholders::_1));
  }

  template <typename... Args>
  void publish(const std::string& topic, Args&&... args) {
    auto range = map_.equal_range(topic);
    for (auto it = range.first; it != range.second; ++it) {
      auto tp = std::make_tuple(std::forward<Args>(args)...);
      it->second(&tp);
    }
  }

 private:
  template <typename F>
  struct invoker {
    static void apply(const F& f, const void* args) {
      using arg_t = typename utility::function_traits<F>::arg_tuple_t;
      const arg_t* tp = static_cast<const arg_t*>(args);
      call(f,
           utility::make_index_sequence<utility::function_traits<F>::arity>{},
           *tp);
    }

    template <size_t... I, typename... Args>
    static void call(const F& f, const utility::index_sequence<I...>&,
                     const std::tuple<Args...>& tp) {
      f(std::get<I>(tp)...);
    }
  };

  std::mutex mutex_;
  std::unordered_multimap<std::string, std::function<void(const void*)>> map_;

  DECLARE_SINGLETON(message_bus);
};

NEW_BASE_END
