// Copyright [year] <Copyright Owner>

#include <csignal>
#include <cstdlib>
#include <atomic>
#include <memory>
#include <utility>
#include <vector>
#include "base/platform.h"
#include "base/config.h"
#include "base/dynamic_lib.h"
#include "base/log.h"
#include "base/node.h"

namespace nb {
namespace platform {
namespace {
typedef std::uint8_t state;
enum /*state : std::uint8_t*/ {
  STATE_UNINITIALIZED = 0,
  STATE_INITIALIZED,
  STATE_SHUTTING_DOWN,
  STATE_SHUTDOWN,
};

std::atomic<state> state_;
std::vector<std::unique_ptr<node_base>> nodes_;

state get_state() { return state_.load(); }

void set_state(const state& s) { state_.store(s); }

bool init() {
  if (get_state() != STATE_UNINITIALIZED) {
    return false;
  }

  std::signal(SIGINT, [](int) {
    if (get_state() != STATE_SHUTDOWN) {
      set_state(STATE_SHUTTING_DOWN);
    }
  });

  if (std::atexit([] {
        if (get_state() == STATE_SHUTDOWN ||
            get_state() == STATE_UNINITIALIZED) {
          return;
        }

        // we can do some cleaning job here

        set_state(STATE_SHUTDOWN);
      })) {
    LOG_E << "Registe atexit handler failed" << std::endl;
    return false;
  }

  set_state(STATE_INITIALIZED);
  return true;
}

void loop() {
  while ((get_state() != STATE_SHUTTING_DOWN) &&
         (get_state() != STATE_SHUTDOWN)) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}
}  // namespace

bool run(const std::string& config_file) {
  if (!init()) {
    return false;
  }

  auto cfg = load_config_from_file(config_file);

  for (auto m : cfg["modules"]) {
    LOG_I << "module_library: " << m["module_library"] << std::endl;
    load_dynamic_lib(m["module_library"].asString());

    for (auto c : m["nodes"]) {
      LOG_I << "class_name: " << c["class_name"] << std::endl;
      auto n = std::unique_ptr<node_base>(create_node_obj(c["class_name"].asString()));
      if (n == nullptr) {
        LOG_E << "create_node_obj " << c["class_name"] << " failed!"
              << std::endl;
        return false;
      }
      if (!n->init(c["config_file_path"].asString())) {
        LOG_E << "init node " << c["class_name"] << " failed!" << std::endl;
        return false;
      }
      LOG_I << "name: " << c["name"] << std::endl;
      LOG_I << "config_file_path: " << c["config_file_path"] << std::endl;
      nodes_.emplace_back(std::move(n));
    }

    for (auto c : m["timer_nodes"]) {
      LOG_I << "class_name: " << c["class_name"] << std::endl;
      auto n = std::unique_ptr<node_base>(create_node_obj(c["class_name"].asString()));
      if (n == nullptr) {
        LOG_E << "create_node_obj " << c["class_name"] << " failed!"
              << std::endl;
        return false;
      }
      if (!n->init(c["config_file_path"].asString(), c["interval"].asInt())) {
        LOG_E << "init timer node " << c["class_name"] << " failed!"
              << std::endl;
        return false;
      }
      LOG_I << "name: " << c["name"] << std::endl;
      LOG_I << "config_file_path: " << c["config_file_path"] << std::endl;
      nodes_.emplace_back(std::move(n));
    }
  }

  loop();

  return true;
}
}  // namespace platform
}  // namespace nb
