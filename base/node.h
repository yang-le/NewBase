#pragma once

#include <string>
#include "base/timer.h"
#include "base/class_factory.h"

class node_base {
public:
    node_base() = default;
    virtual ~node_base() = default;

    virtual bool init(const std::string& cfg_file_path) { return false; };
    virtual bool init(unsigned int interval, const std::string& cfg_file_path) { return false; };
};

class node : public node_base {
public:
    virtual bool init(const std::string& cfg_file_path) override {
        return initialize(cfg_file_path);
    }

private:
    virtual bool initialize(const std::string& cfg_file_path) = 0;
};

class timer_node : public node_base {
public:
    virtual bool init(unsigned int interval, const std::string& cfg_file_path) override {
        if (!initialize(cfg_file_path)) {
            return false;
        }

        t_.start(interval, [this] {
            process();
        });

        return true;
    }

private:
    virtual bool initialize(const std::string& cfg_file_path) = 0;
    virtual void process() = 0;

private:
    timer t_;
};

node_base* create_node_obj(const std::string& class_name) {
    return create_class_obj<node_base>(class_name);
}

#define NODE_REGIST(n) CLASS_FACTORY_REGIST(n, node_base)
