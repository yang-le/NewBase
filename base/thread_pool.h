// Copyright [year] <Copyright Owner>

#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>
#include "base/macros.h"

namespace nb {
class thread_pool {
 public:
  using task_t = std::function<void()>;

  template <typename F, typename... Args>
  std::future<typename std::result_of<F(Args...)>::type> commit(
      F&& f, Args&&... args) {
    if (stopped_) {
      throw std::runtime_error("thread_pool is stopped.");
    }

    using return_type = decltype(f(args...));
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    {
      std::lock_guard<std::mutex> lock(mutex_);
      tasks_.emplace([task] { (*task)(); });
    }
    ready_.notify_one();

    return task->get_future();
  }

 private:
  std::queue<task_t> tasks_;
  std::vector<std::thread> threads_;
  std::atomic_bool stopped_;
  std::mutex mutex_;
  std::condition_variable ready_;

  DECLARE_SINGLETON(thread_pool);
};
}  // namespace nb
