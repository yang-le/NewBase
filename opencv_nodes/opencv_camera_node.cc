#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include "base/camera_node.h"

class opencv_camera_node : public nb::camera_node {
private:
    bool initialize(const std::string& cfg) override {
        if (!camera_node::initialize(cfg)) {
            return false;
        }
        
        if (!cap_.open(source_, cv::CAP_FFMPEG)) {
            return false;
        }

        cap_ >> image_;

        return true;
    }

private:
    void process() override {
        nb::message_bus::instance().publish(topic_, &image_);
        cap_ >> image_;
    }

    cv::VideoCapture cap_;
    cv::Mat image_;
};

NODE_REGIST(opencv_camera_node);
