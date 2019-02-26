// Copyright [year] <Copyright Owner>

#pragma once

#include <string>
#include "base/class_factory.h"
#include "base/macros.h"
#include "base/timer.h"

namespace nb {
class node_base {
 public:
  virtual ~node_base() = default;
  virtual bool init(const std::string& /* cfg_file_path */,
                    unsigned int /* interval */ = 0) = 0;
};

class node : public node_base {
 public:
  bool init(const std::string& cfg_file_path, unsigned int) override {
    return initialize(cfg_file_path);
  }

 private:
  virtual bool initialize(const std::string& cfg_file_path) = 0;
};

class timer_node : public node_base {
 public:
  bool init(const std::string& cfg_file_path, unsigned int interval) override {
    if (!initialize(cfg_file_path)) {
      return false;
    }

    timer::instance().start(interval, [this] { process(); });

    return true;
  }

 private:
  virtual bool initialize(const std::string& cfg_file_path) = 0;
  virtual void process() = 0;
};

NEW_BASE_EXPORT node_base* create_node_obj(const std::string& class_name);
}  // namespace nb

#define NODE_REGIST(n) \
  using nb::node_base; \
  CLASS_FACTORY_REGIST(n, node_base)
