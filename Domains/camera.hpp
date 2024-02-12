// Piotr Pedziwiatr
// 02/2024

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <pthread.h>
#include <queue>
#include <chrono>
#include "frame.hpp"
#include "framecollection.hpp"

using json = nlohmann::json;

struct Camera
{
    Camera(std::string name, std::string conectionString);
    Camera(json configObject);
    int activate();
    int deactivate();
    void attachLogger(spdlog::logger *);

private:
    std::string conectionString, name;
    bool active;
    cv::Mat currentFrame;
    spdlog::logger *logger;
    static void *mainLoop_helper(void *context);
    void *mainLoop();
    std::unique_ptr<cv::VideoCapture> cap;
    pthread_t camera_thread;
    int collectedFrames = 0;
    FrameCollection frames;
};

#endif // CAMERA_HPP