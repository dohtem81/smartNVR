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
#include "../smartNVR.Domain/frame.hpp"
#include "../smartNVR.Domain/camerafeatures.hpp"
#include <memory>
#include "videomaker.hpp"
#include "../smartNVR.Domain/framecollection.hpp"
#include <sstream>
#include "framesaver.hpp"
#include "../Common/iCamera.hpp"
#include "../Common/FileLocation.hpp"

using json = nlohmann::json;

struct Camera : public iCamera
{
    Camera(std::string name, std::string conectionString);
    Camera(json configObject);
    int activate();
    int deactivate();
    void attachLogger(spdlog::logger *);
    bool isConected() { return this->conectionEstablished; }
    void saveCurrentFrame();
    std::string to_string();

    void SaveLastFrame(FileLocation);
    void SaveFrameBufferAsFrames(FileLocation);   
    std::shared_ptr<CameraFeatures> GetFeatures() const;

    // iCamera interface
    std::shared_ptr<Frame> GetLastFrame() const;
    std::shared_ptr<FrameCollection> GetFrameCollection() const;
    void EmptyFrameCollection();
    bool IsStreaming() const;

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
    std::shared_ptr<FrameCollection> frames_ptr;
    bool conectionEstablished;
    std::shared_ptr<CameraFeatures> features;
    int bufferSize;
    void VideoMakerBuilder();
};

#endif // CAMERA_HPP