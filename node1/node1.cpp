#include "base/log.h"
#include "base/node.h"
#include "vld.h"

class node1 final : public timer_node {
    virtual bool initialize(const std::string& cfg) override {
        LOG_I << "I'm node1" << std::endl;

        t.start_once(10, [] {
            LOG_I << "say:" << std::endl;
        });

        for (int i = 1; i < 10; ++i) {
            t.start_once(i * 100, [i] {
                LOG_I << i << std::endl;
            });
        }

        return true;
    }

    virtual void process() override {
        LOG_I << "hello" << std::endl;
    }

    timer t;
};

NODE_REGIST(node1);
