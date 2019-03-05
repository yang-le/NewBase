#pragma once

#include <string>
#include "base/node.h"
#include "base/log.h"
#include "base/message_bus.h"
#include "base/config.h"

namespace nb {
    class render_node : public timer_node {
    protected:
        bool initialize(const std::string& cfg) override {
            auto render_conf = load_config_from_file(cfg);

            topic_ = render_conf["topic"].asString();

            return true;
        }

        std::string topic_;
    };
};
