#include "base/log.h"
#include "base/node.h"
#include "base/message_bus.h"

using namespace nb;

class node1 final : public timer_node {
    virtual bool initialize(const std::string& cfg) override {
        LOG_I << "I'm node1" << std::endl;

        get_message_bus().subscribe("echo_topic", [] (const char* reply) {
            LOG_I << "[node1] Echo: " << reply << std::endl;
        });

        return true;
    }

    virtual void process() override {
        get_message_bus().publish("demo_topic", "hello from node1");
    }
};

NODE_REGIST(node1);
