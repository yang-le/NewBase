// Copyright [year] <Copyright Owner>

#include "base/log.h"
#include "base/message_bus.h"
#include "base/node.h"
#include "base/system_nodes.h"

namespace nb {
namespace system_node {
class monitor_node : public timer_node {
 private:
  bool initialize(const std::string& /* cfg */) override { return true; }

  void process() override {
    auto topics = nb::message_bus::instance().get_topics();
    nb::message_bus::instance().publish("channels", topics);
    for (auto topic : topics) {
      LOG_I << topic;
    }
  }
};
}  // namespace system_node
}  // namespace nb

SYSTEM_NODE_REGIST(monitor_node, 1000);
