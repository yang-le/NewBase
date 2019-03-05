// Copyright [year] <Copyright Owner>

#include "base/log.h"
#include "base/message_bus.h"
#include "base/thread_pool.h"
#include "base/system_nodes.h"

namespace nb {
namespace system_nodes {
class monitor_node : public timer_node {
 private:
  bool initialize(const std::string& /* cfg */) override { return true; }

  void process() override {
    auto topics = message_bus::instance().get_topics();
    message_bus::instance().publish("message_channels", topics);
    LOG_I << "message_channels:";
    for (auto topic : topics) {
      LOG_I << '\t' << topic;
    }

    auto timer_queue_size = timer::instance().get_queue_size();
    message_bus::instance().publish("timer_queue_size", timer_queue_size);
    LOG_I << "timer_queue_size: " << timer_queue_size;

    auto task_queue_size = thread_pool::instance().get_queue_size();
    message_bus::instance().publish("timer_queue_size", task_queue_size);
    LOG_I << "task_queue_size: " << task_queue_size;
  }
};

SYSTEM_NODE_REGIST(monitor_node, 1000);
}  // namespace system_nodes
}  // namespace nb
