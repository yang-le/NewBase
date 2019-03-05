// Copyright [year] <Copyright Owner>

#pragma once

#include <string>
#include "base/class_factory.h"
#include "base/macros.h"
#include "base/timer.h"
#include "base/log.h"

namespace nb {
class node_base {
 public:
  virtual ~node_base() = default;

  bool init() { return init("", 0); }
  bool init(const std::string& cfg_file_path) {
    return init(cfg_file_path, 0);
  }
  bool init(unsigned int interval) { return init("", interval); }
  virtual bool init(const std::string& /* cfg_file_path */,
                    unsigned int /* interval */) = 0;

 protected:
  virtual bool initialize(const std::string& cfg_file_path) = 0;
};

class node : public node_base {
 public:
  bool init(const std::string& cfg_file_path,
            unsigned int /* interval */) override {
    return initialize(cfg_file_path);
  }
};

class timer_node : public node_base {
 public:
  bool init(const std::string& cfg_file_path, unsigned int interval) override {
    if (!initialize(cfg_file_path)) {
      return false;
    }

    timer::instance().start(interval, [this] {
        try {
            process();
        } catch (std::exception e) {
            LOG_I << e.what();
        } catch (...) {
            LOG_I << "unknow exception";
        }
    });

    return true;
  }

 private:
  virtual void process() = 0;
};

class thread_node : public node_base {
public:
    bool init(const std::string& cfg_file_path,
        unsigned int /* interval */) override {
        if (!initialize(cfg_file_path)) {
            return false;
        }

        std::thread([this] {
            try {
                process();
            } catch (std::exception e) {
                LOG_I << e.what();
            } catch (...) {
                LOG_I << "unknow exception";
            }
        }).detach();

        return true;
    }

private:
    virtual void process() = 0;
};

NEW_BASE_EXPORT node_base* create_node_obj(const std::string& class_name);
}  // namespace nb

#define NODE_REGIST(n) \
  using nb::node_base; \
  CLASS_FACTORY_REGIST(n, node_base)
