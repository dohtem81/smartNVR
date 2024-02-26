// Piotr Pedziwiatr
// 02/2024

#include "camera.hpp"
#include "framesaver.hpp"

void Camera::attachLogger(spdlog::logger* _logger)
{
    logger = _logger;

    return;
}

// -------------
Camera::Camera(std::string name, std::string conectionString) : 
        conectionString(conectionString),
        name(name),
        conectionEstablished(false),
        active(false),
        frames(100) {}

// -------------
Camera::Camera(json configObject) : 
        conectionEstablished(false),
        active(false)
{
    conectionString = configObject["connectionstring"];
    name = configObject["name"];
    frames = FrameCollection(configObject["buffersize"]);
}

// -------------
int Camera::activate()
{
    int retry = 0;
    // if (active)
    // {
    //     spdlog::error("Connection string >>" + conectionString + " already active [FAILED]");
    //     return -1;
    // }
    active = true;
    cap = std::make_unique<cv::VideoCapture>();
    spdlog::info("Connection string >>" + conectionString);
    cap->open(conectionString);
    if (cap->isOpened())
    {
        this->features = CameraFeatures::CameraFeaturesFactory(cap.get());
        spdlog::info(conectionString + " features " + CameraFeatures::to_string(features));
    }
    while (!cap->isOpened())
    {
        spdlog::error("Connection string >>" + conectionString + " [FAILED]"); 
        cap.release();

        // retry to connect
        if (retry++ < 3)
        {
            spdlog::info("Connection string >>" + conectionString);
            cap->open(conectionString);
        }
        else
        {
            cap.release();
            spdlog::error("Connection string >>" + conectionString + " [FAILED]"); 
            return -1;
        }
    }

    conectionEstablished = true;
    pthread_create(&camera_thread, NULL, Camera::mainLoop_helper, this);
    spdlog::info("Connection string >>" + conectionString + " [SUCCESS]");
    return 0;
}

// -------------
int Camera::deactivate()
{
    active = false;
    // wait here until camera bgets deactivated
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
        if (cap->read(currentFrame))
        {
            Frame frameToAdd;
            currentFrame.copyTo(frameToAdd);
            collectedFrames++;
            frames.addFrame(std::make_shared<Frame>(frameToAdd));
        }
    }

    cap->release();
    spdlog::info("Stopping >>" + conectionString + " [SUCCESS]");
    return 0;
}

// -------------
Frame* Camera::returnLastFrame()
{
    return &(this->currentFrame);
}

// -------------
void Camera::saveCurrentFrame()
{
    std::string fn = this->name + ".jpg";
    FrameSaver::SaveFrame(FileLocation("./", fn), frames.getFrame(frames.getSize() - 1).get());

    return;
}