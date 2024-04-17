// Piotr Pedziwiatr
// 02/2024

#ifndef VIDEOMAKER_HPP
#define VIDEOMAKER_HPP

#include <memory>
#include <opencv2/opencv.hpp>
#include "../smartNVR.Domain/camerafeatures.hpp"
#include "../smartNVR.Domain/frame.hpp"
#include "../smartNVR.Domain/framecollection.hpp"
#include "../Common/FileLocation.hpp"

#include "framesaver.hpp"

class VideoMaker
{
public:
    // this factory is used to save frame collection as a video file
    static std::shared_ptr<VideoMaker> VideoMakerFactory(
        std::shared_ptr<FileLocation>,
        std::shared_ptr<CameraFeatures>,
        std::shared_ptr<FrameCollection>);

    // this factory creates sink where live stream will be saved
    static std::shared_ptr<VideoMaker> VideoMakerFactory(
        std::shared_ptr<FileLocation>,
        std::shared_ptr<CameraFeatures>);

    int addFrame(std::shared_ptr<Frame>);
    int addFrames(std::shared_ptr<FrameCollection>);
    int CreateVideo(FrameCollection);
private:
    VideoMaker(
        std::shared_ptr<FileLocation>,
        std::shared_ptr<CameraFeatures>
    );

    std::unique_ptr<cv::VideoWriter> videoSink;
    std::string pathAndFile;
};

#endif // VIDEOMAKER_HPP