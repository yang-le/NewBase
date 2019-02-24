#include "base/log.h"
#include "base/node.h"
#include "base/message_bus.h"

using namespace nb;

class node2 final : public node {
private:
    virtual bool initialize(const std::string& /* cfg */) override {
        LOG_I << "I'm node2" << std::endl;

        message_bus::instance().subscribe("demo_topic", [] (const char* message){
            LOG_I << "[node2] Recv: " << message << std::endl;
            message_bus::instance().publish("echo_topic", message);
        });

        return true;
    }
};

NODE_REGIST(node2);
