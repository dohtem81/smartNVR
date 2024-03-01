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
#include "icamera.hpp"
#include <memory>
#include "icapturefeatures.hpp"
#include "camerafeatures.hpp"
#include <sstream>
#include "videomaker.hpp"

using json = nlohmann::json;

struct Camera : ICamera
{
    Camera(std::string name, std::string conectionString);
    Camera(json configObject);
    int activate();
    int deactivate();
    void attachLogger(spdlog::logger *);
    bool isConected() { return this->conectionEstablished; }
    void saveCurrentFrame();
    std::string to_string();

private:
    std::string conectionString, name, savePath;
    bool active;
    Frame currentFrame;
    spdlog::logger *logger;
    static void *mainLoop_helper(void *context);
    void *mainLoop();
    std::shared_ptr<cv::VideoCapture> cap;
    pthread_t camera_thread;
    int collectedFrames = 0;
    FrameCollection frames;
    bool conectionEstablished;
    std::shared_ptr<CameraFeatures> features;
    int bufferSize;
    std::shared_ptr<VideoMaker> videoMaker;

    virtual std::shared_ptr<Frame> returnLastFrame(); // from interface
    void VideoMakerBuilder();
};

#endif // CAMERA_HPP