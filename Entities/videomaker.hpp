// Piotr Pedziwiatr
// 02/2024

#ifndef VIDEOMAKER_HPP
#define VIDEOMAKER_HPP

#include <memory>
#include <opencv2/opencv.hpp>
#include "camerafeatures.hpp"
#include "filelocation.hpp"
#include "frame.hpp"

class VideoMaker
{
public:
    static std::shared_ptr<VideoMaker> VideoMakerFactory(
        std::shared_ptr<FileLocation>,
        std::shared_ptr<CameraFeatures>);
    int addFrame(std::shared_ptr<Frame>);

private:
    VideoMaker(
        std::shared_ptr<FileLocation>,
        std::shared_ptr<CameraFeatures>
    );

    std::unique_ptr<cv::VideoWriter> videoSink;
};

#endif // VIDEOMAKER_HPP