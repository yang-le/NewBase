#include <mutex>
#include <opencv2/highgui.hpp>
#include "base/render_node.h"

class opencv_render_node : public nb::render_node {
private:
    bool initialize(const std::string& cfg) override {
        if (!render_node::initialize(cfg)) {
            return false;
        }

        valid_ = false;

        nb::message_bus::instance().subscribe(topic_, [this](cv::Mat image) {
            std::lock_guard<std::mutex> lock(mutex_);
            image_ = std::move(image);
            valid_ = true;
        });

        return true;
    }

private:
    void process() override {
        for (;;) {
            if (valid_) {
                std::lock_guard<std::mutex> lock(mutex_);
                cv::imshow("opencv_render", image_);
                valid_ = false;
            }
            cv::waitKey(1);
        }
    }

    cv::Mat image_;
    bool valid_;
    std::mutex mutex_;
};

NODE_REGIST(opencv_render_node);
