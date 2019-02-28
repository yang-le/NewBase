// Copyright [year] <Copyright Owner>

#include "base/timer.h"
#include "base/thread_pool.h"

namespace nb {
DEFINE_SINGLETON(timer);

timer::timer() : stopped_(false) {
  thread_ = std::thread([this] {
    while (!stopped_ || !tasks_.empty()) {
      std::this_thread::sleep_for(1_ms);

      if (!tasks_.empty()) {
        task t = std::move(tasks_.top());
        if (std::chrono::high_resolution_clock::now() > t.dead_line_) {
          {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.pop();
          }
          thread_pool::instance().commit([t] {
              t.func_();
          });
        }
      }
    }
  });
}

timer::~timer() {
  stopped_ = true;
  if (thread_.joinable()) {
    thread_.join();
  }
}
}  // namespace nb
