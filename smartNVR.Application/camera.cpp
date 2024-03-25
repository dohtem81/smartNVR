/**
 * @file camera.cpp
 * @brief Implementation of the Camera class.
 * 
 * This file contains the implementation of the Camera class, which represents a camera device.
 * The Camera class provides functionality to connect to a camera, capture frames, and perform various operations on the frames.
 */

#include "camera.hpp"

// -------------
/**
 * @brief Attaches a logger to the Camera object.
 * 
 * @param _logger A pointer to the logger object.
 */
void Camera::attachLogger(spdlog::logger* _logger)
{
    logger = _logger;

    return;
}

// -------------
/**
 * @brief Constructs a Camera object with the given name and connection string.
 * 
 * @param name The name of the camera.
 * @param conectionString The connection string of the camera.
 */
Camera::Camera(std::string name, std::string conectionString) : 
        conectionString(conectionString),
        name(name),
        conectionEstablished(false),
        active(false) {}

// -------------
/**
 * @brief Constructs a Camera object from a JSON configuration object.
 * 
 * @param configObject The JSON configuration object containing camera settings.
 */
Camera::Camera(json configObject) : 
        conectionEstablished(false),
        active(false),
        conectionString(configObject["connectionstring"]),
        name(configObject["name"]),
        savePath(configObject["saveframepath"])
{
    frames_ptr = std::make_shared<FrameCollection>(FrameCollection(configObject["buffersize"]));
}

// -------------
/**
 * @brief Activates the camera connection and starts capturing frames.
 * 
 * @return 0 if the activation is successful, -1 otherwise.
 */
int Camera::activate()
{
    // int retry = 0;
    // if (this->active)
    // {
    //     spdlog::error("Connection string >>" + conectionString + " already active [FAILED]");
    //     return -1;
    // }
    // active = true;
    // cap = std::make_shared<cv::VideoCapture>();
    // spdlog::info("Connection string >>" + conectionString);
    // cap->open(conectionString);
    // if (cap->isOpened())
    // {
    //     this->features = CameraFeatures::CameraFeaturesFactory(cap);
    //     spdlog::info(conectionString + " features " + CameraFeatures::to_string(features));
    // }
    // while (!cap->isOpened())
    // {
    //     spdlog::error("Connection string >>" + conectionString + " [FAILED]"); 
    //     cap->release();

    //     // retry to connect
    //     if (retry++ < 3)
    //     {
    //         spdlog::info("Connection string >>" + conectionString);
    //         cap->open(conectionString);
    //     }
    //     else
    //     {
    //         cap->release();
    //         spdlog::error("Connection string >>" + conectionString + " [FAILED]"); 
    //         return -1;
    //     }
    // }

    // conectionEstablished = true;
    active = true;
    pthread_create(&camera_thread, NULL, Camera::mainLoop_helper, this);
    return 0;
}

// -------------
/**
 * @brief Deactivates the camera connection and stops capturing frames.
 * 
 * @return 0 if the deactivation is successful.
 */
int Camera::deactivate()
{
    active = false;
    // wait here until camera gets deactivated
    pthread_join(camera_thread, NULL);

    spdlog::info("collected frames count for " + conectionString + " >>> " + std::to_string(frames_ptr->getSize()));
    return 0;
}

// -------------
/**
 * @brief Helper function for the camera thread's main loop.
 * 
 * @param context A pointer to the Camera object.
 * @return The result of the main loop.
 */
void *Camera::mainLoop_helper(void *context)
{
    return ((Camera *)context)->mainLoop();
}

// -------------
/**
 * @brief The main loop of the camera thread.
 * 
 * @return The result of the main loop.
 */
void *Camera::mainLoop()
{
    int retryConncetion = 0;
    cap = std::make_shared<cv::VideoCapture>();

    while(active)
    {
        // if cap is not opened, try to open it
        if (!cap->isOpened())
        {
            retryConncetion++;
            cap->open(conectionString);
            if (cap->isOpened())
            {
                this->features = CameraFeatures::CameraFeaturesFactory(cap);
                spdlog::info(conectionString + " [SUCCESS]" + " >>> features " + CameraFeatures::to_string(features));
                // reset rety countyer for the future
                retryConncetion = 0;
            }
            else
            {
                if (retryConncetion > 3)
                {
                    spdlog::error(conectionString + " [FAILED]"); 
                    break;
                }
            }
        }
        else // this is the case when cap is opened
        {
            if (cap->read(currentFrame))
            {
                Frame frameToAdd;
                currentFrame.copyTo(frameToAdd);
                collectedFrames++;
                frames_ptr->addFrame(std::make_shared<Frame>(frameToAdd));
            }
        }
    }

    cap->release();
    spdlog::info("Stopping >>" + conectionString + " [SUCCESS]");
    return 0;
}

// -------------
/**
 * @brief Saves the current frame to a file.
 */
void Camera::saveCurrentFrame()
{
    std::string fn = this->name + ".jpg";
    FrameSaver::SaveFrame(FileLocation("./", fn), frames_ptr->getFrame(frames_ptr->getSize() - 1));

    return;
}

// string representation of the camera
// ----------------------------------
/**
 * @brief Returns a string representation of the Camera object.
 * 
 * @return A string representation of the Camera object.
 */
std::string Camera::to_string()
{
    // update features
    this->features = CameraFeatures::CameraFeaturesFactory(cap);
    // print values
    std::ostringstream oss;
    oss << this->name << " >> " << this->features->to_string();
    return oss.str();
}

// return last frame from collection
// ---------------------------------
/**
 * @brief Returns the last captured frame from the frame collection.
 * 
 * @return A shared pointer to the last captured frame.
 */
std::shared_ptr<Frame> Camera::GetLastFrame() const
{
    return std::make_shared<Frame>(this->currentFrame);
}

// return entire frame collection
// ------------------------------
/**
 * @brief Returns the entire frame collection.
 * 
 * @return A shared pointer to the frame collection.
 */
std::shared_ptr<FrameCollection> Camera::GetFrameCollection() const
{
    return frames_ptr;
}

// camera features getter
// -----------------------
/**
 * @brief Returns the camera features.
 * 
 * @return A shared pointer to the camera features.
 */
std::shared_ptr<CameraFeatures> Camera::GetFeatures() const
{
    return features;
}


/**
 * Checks if the camera is currently streaming.
 *
 * @return true if the camera is streaming, false otherwise.
 */
bool Camera::IsStreaming() const
{
    bool ret = false;
    try 
    {
        ret = active && cap->isOpened();
    }
    catch (const std::exception& e)
    {
        ret = false;
    }

    return ret;
}