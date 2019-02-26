// Copyright [year] <Copyright Owner>

#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <memory>
#include <utility>

#include "base/chrono_literals.h"
#include "base/macros.h"

NEW_BASE_BEGIN

using chrono_literals::operator"" _ms;

class timer {
 public:
  template <typename F, typename... Args>
  void start(unsigned int interval, F&& f, Args&&... args) {
      std::function<void()> task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
      start(interval, task);
  }

  void start(unsigned int interval, std::function<void()> f) {
      if (!stopped_) {
          std::lock_guard<std::mutex> lock(mutex_);
          tasks_.emplace([=] {
              f();
              start(interval, f);
          },
              std::chrono::high_resolution_clock::now() +
              std::chrono::milliseconds(interval));
      }
  }

  template <typename F, typename... Args>
  std::future<typename std::result_of<F(Args...)>::type> start_once(
      unsigned int interval, F&& f, Args&&... args) {
    using return_type = decltype(f(args...));
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    if (!stopped_) {
      std::lock_guard<std::mutex> lock(mutex_);
      tasks_.emplace([task] { (*task)(); },
                     std::chrono::high_resolution_clock::now() +
                         std::chrono::milliseconds(interval));
    }

    return task->get_future();
  }

 private:
  struct task {
    using time_point =
        std::chrono::time_point<std::chrono::high_resolution_clock>;

    template <typename F>
    task(F func, time_point&& dead_line)
        : func_(func), dead_line_(std::move(dead_line)) {}

    bool operator<(const task& rhd) const {
      return dead_line_ > rhd.dead_line_;
    }

    std::function<void()> func_;
    time_point dead_line_;
  };

  std::priority_queue<task> tasks_;
  std::thread thread_;
  std::atomic_bool stopped_;
  std::mutex mutex_;

  DECLARE_SINGLETON(timer);
};

NEW_BASE_END
