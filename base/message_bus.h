// Copyright [year] <Copyright Owner>

#pragma once

#define USE_THREAD_POOL 0

#include <string>
#include <unordered_map>
#include <functional>
#include <mutex>
#include <tuple>
#include "base/function_traits.h"
#if USE_THREAD_POOL
#include "base/thread_pool.h"
#endif
#include "base/macros.h"

NEW_BASE_BEGIN

class message_bus {
 public:
    message_bus() = default;

    template <typename F>
    void regist_handler(const std::string& topic, const F& f) {
        std::lock_guard<std::mutex> lock(mutex_);
        map_.emplace(topic,
            std::bind(&invoker<F>::apply, f, std::placeholders::_1));
    }

    template <typename... Args>
    void call(const std::string& topic, Args&&... args) {
        auto range = map_.equal_range(topic);
        for (auto it = range.first; it != range.second; ++it) {
            auto tp = std::make_tuple(std::forward<Args...>(args)...);
#if USE_THREAD_POOL
            pool_.commit([it, tp] {
#endif
                it->second(&tp);
#if USE_THREAD_POOL
            });
#endif
        }
    }

 private:
    template <typename F>
    struct invoker {
        static void apply(const F& f, const void *args) {
            using arg_t = function_traits<F>::arg_tuple_t;
            const arg_t* tp = static_cast<const arg_t*>(args);
            call(f,
                std::make_index_sequence<function_traits<F>::num_args>{}, *tp);
        }

        template <typename F, size_t... I, typename... Args>
        static void call(
            const F& f,
            const std::index_sequence<I...>&,
            const std::tuple<Args...>& tp) {
            f(std::get<I>(tp)...);
        }
    };

    std::mutex mutex_;
    std::unordered_multimap<std::string, std::function<void(const void*)>> map_;
#if USE_THREAD_POOL
    thread_pool pool_;
#endif

    DISALLOW_COPY_AND_ASSIGN(message_bus);
};

NEW_BASE_END
