// Copyright [year] <Copyright Owner>

#include "base/thread_pool.h"

namespace nb {
    DEFINE_SINGLETON(thread_pool);

    thread_pool::thread_pool()
        : stopped_(false) {
        for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i) {
            threads_.emplace_back([this] {
                while (!stopped_ || !tasks_.empty()) {
                    task_t task;
                    {
                        std::unique_lock<std::mutex> lock(mutex_);
                        ready_.wait(lock, [this] {
                            // wait until stopped or recv task.
                            return stopped_ || !tasks_.empty();
                        });

                        if (!tasks_.empty()) {
                            task = std::move(tasks_.front());
                            tasks_.pop();
                        }
                    }
                    if (task.target_type() != typeid(void)) {
                        task();
                    }
                }
            });
        }
    }

    thread_pool::~thread_pool() {
        stopped_ = true;
        ready_.notify_all();
        for (auto& thread : threads_) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }
}
