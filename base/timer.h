// Copyright [year] <Copyright Owner>

#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

#include "base/macros.h"

namespace nb {
class timer {
 public:
  template <typename F, typename... Args>
  void start(unsigned int interval, F&& f, Args&&... args) {
    std::function<void()> task =
        std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    start(interval, task);
  }

  void start(unsigned int interval, std::function<void()> f) {
    if (!stopped_) {
      std::lock_guard<std::mutex> lock(mutex_);
      tasks_.emplace(
          [=] {
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
    typedef decltype(f(args...)) return_type;
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
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;

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

}  // namespace nb
