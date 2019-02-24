#include "base/log.h"
#include "base/node.h"
#include "base/message_bus.h"

using namespace nb;

class node1 final : public timer_node {
private:
    virtual bool initialize(const std::string& /* cfg */) override {
        LOG_I << "I'm node1" << std::endl;

        message_bus::instance().subscribe("echo_topic", [] (const char* reply) {
            LOG_I << "[node1] Echo: " << reply << std::endl;
        });

        return true;
    }

    virtual void process() override {
        message_bus::instance().publish("demo_topic", "hello from node1");
    }
};

NODE_REGIST(node1);
