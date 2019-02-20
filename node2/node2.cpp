#include "base/log.h"
#include "base/node.h"
#include "base/message_bus.h"

using namespace nb;

class node2 final : public node {
    virtual bool initialize(const std::string& cfg) override {
        LOG_I << "I'm node2" << std::endl;

        get_message_bus().subscribe("demo_topic", [] (const char* message){
            LOG_I << "[node2] Recv: " << message << std::endl;
            get_message_bus().publish("echo_topic", message);
        });

        return true;
    }
};

NODE_REGIST(node2);
