#pragma once

#include <string>
#include "base/node.h"
#include "base/log.h"
#include "base/message_bus.h"
#include "base/config.h"

namespace nb {
    class camera_node : public timer_node {
    protected:
        bool initialize(const std::string& cfg) override {
            auto camera_conf = load_config_from_file(cfg);

            topic_ = camera_conf["topic"].asString();
            source_ = camera_conf["source"].asString();

            return true;
        }

        std::string topic_;
        std::string source_;
    };
};
