// Copyright [year] <Copyright Owner>

#include "base/log.h"
#include "base/message_bus.h"
#include "base/node.h"
#include "base/system_nodes.h"

namespace nb {
namespace system_nodes {
class monitor_node : public timer_node {
 private:
  bool initialize(const std::string& /* cfg */) override { return true; }

  void process() override {
    auto topics = nb::message_bus::instance().get_topics();
    nb::message_bus::instance().publish("message_channels", topics);
    LOG_I << "message_channels:";
    for (auto topic : topics) {
      LOG_I << '\t' << topic;
    }

    auto queue_size = nb::timer::instance().get_queue_size();
    nb::message_bus::instance().publish("timer_queue_size", queue_size);
    LOG_I << "timer_queue_size: " << queue_size;
  }
};

SYSTEM_NODE_REGIST(monitor_node, 1000);
}  // namespace system_nodes
}  // namespace nb
