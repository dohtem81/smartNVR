// Piotr Pedziwiatr
// 02/2024

#include "camera.hpp"

void Camera::attachLogger(spdlog::logger* _logger)
{
    logger = _logger;

    return;
}

// -------------
Camera::Camera(std::string name, std::string conectionString) : 
        conectionString(conectionString),
        name(name) {}

// -------------
Camera::Camera(json configObject) 
{
    conectionString = configObject["connectionstring"];
    name = configObject["name"];
}

// -------------
int Camera::activate()
{
    if (active)
    {
        spdlog::error("Connection string >>" + conectionString + " already active [FAILED]");
        return -1;
    }
    active = true;
    cap = std::make_unique<cv::VideoCapture>();
    spdlog::info("Connection string >>" + conectionString);
    cap->open(conectionString);
    if (!cap->isOpened())
    {
        spdlog::error("Connection string >>" + conectionString + " [FAILED]");
        cap.release();
        return -1;
    }

    spdlog::info("Connection string >>" + conectionString + " [SUCCESS]");
    pthread_create(&camera_thread, NULL, Camera::mainLoop_helper, this);
    return 0;
}

// -------------
int Camera::deactivate()
{
    active = false;
    pthread_join(camera_thread, NULL);
    spdlog::info("collected frames count for " + conectionString + " >>> " + std::to_string(frames.getSize()));
    return 0;
}

// -------------
void *Camera::mainLoop_helper(void *context)
{
    return ((Camera *)context)->mainLoop();
}

// -------------
void *Camera::mainLoop()
{
    while(active && cap->isOpened())
    {
        cap->read(currentFrame);
        collectedFrames++;
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        Frame *temp_frame = new Frame(&currentFrame); 
        frames.addFrame(temp_frame);
    }

    cap->release();
    spdlog::info("Stopping >>" + conectionString + " [SUCCESS]");
    return 0;
}