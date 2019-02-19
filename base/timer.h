#pragma once

#include <thread>
#include <atomic>
#include <functional>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>

using namespace std::chrono_literals;

class timer {
public:
    struct task {
        using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;

        template <typename F>
        task(F func, time_point& dead_line) : func_(func), dead_line_(dead_line) {}

        bool operator< (const task& rhd) const { return dead_line_ > rhd.dead_line_; }

        std::function<void()> func_;
        time_point dead_line_;
    };

    timer() : stopped_(false) {
        thread_ = std::thread([this] {
            while (!stopped_ || !tasks_.empty()) {
                std::this_thread::sleep_for(1ms);

                if (!tasks_.empty()) {
                    task t = std::move(tasks_.top());
                    if (std::chrono::high_resolution_clock::now() < t.dead_line_) {
                        continue;
                    }
                    {
                        std::unique_lock<std::mutex> lock(mutex_);
                        tasks_.pop();
                    }
                    t.func_();
                }
            }
        });
    }

    ~timer() {
        stopped_ = true;
        if (thread_.joinable()) {
            thread_.join();
        }
    }

    template <typename F, typename... Args>
    std::future<typename std::result_of<F(Args...)>::type>
    start(unsigned int interval, F&& f, Args&&... args) {
        return commit(false, interval, std::forward<F>(f), std::forward<Args...>(args)...);
    }

    template <typename F, typename... Args>
    std::future<typename std::result_of<F(Args...)>::type>
    start_once(unsigned int interval, F&& f, Args&&... args) {
        return commit(true, interval, std::forward<F>(f), std::forward<Args...>(args)...);
    }

private:
    template <typename F, typename... Args>
    std::future<typename std::result_of<F(Args...)>::type>
        commit(bool one_shot, unsigned int interval, F&& f, Args&&... args) {
        using return_type = decltype(f(args...));
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args...>(args)...));

        if (stopped_) {
            //throw std::runtime_error("timer is stopped.");
            return task->get_future();
        }

        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (one_shot) {
                tasks_.emplace([task] {
                    (*task)();
                }, std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(interval));
            }
            else {
                tasks_.emplace([=] {
                    (*task)();
                    commit(false, interval, f, args...);
                }, std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(interval));
            }
        }

        return task->get_future();
    }

private:
    std::priority_queue<task> tasks_;
    std::thread thread_;
    std::atomic_bool stopped_;
    std::mutex mutex_;
};
