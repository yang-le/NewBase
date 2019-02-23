#pragma once

#include <string>
#include <memory>
#include "base/timer.h"
#include "base/class_factory.h"
#include "base/macros.h"

NEW_BASE_BEGIN

class node_base : public std::enable_shared_from_this<node_base> {
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

	std::weak_ptr<timer_node> self = std::dynamic_pointer_cast<timer_node>(shared_from_this());
        t_.start(interval, [self] {
	    auto ptr = self.lock();
	    if (ptr) {
            	ptr->process();
	    }
        });

        return true;
    }

private:
    virtual bool initialize(const std::string& cfg_file_path) = 0;
    virtual void process() = 0;

private:
    timer t_;
};

NEW_BASE_API std::shared_ptr<node_base> create_node_obj(const std::string& class_name);

NEW_BASE_END

#define NODE_REGIST(n) CLASS_FACTORY_REGIST(n, node_base)
