// Piotr Pedziwiatr
// 02/2024

#include "videomaker.hpp"

// private constructor, used by VideoMakerFactory
// ----------------------------------------------
VideoMaker::VideoMaker(
    std::shared_ptr<FileLocation> _fileLocation,
    std::shared_ptr<CameraFeatures> _camFeatures
)
{
    // backend -> from camera features
    // features -> from camera features
    // filename
    videoSink = std::make_unique<cv::VideoWriter>(
        _fileLocation->Path + _fileLocation->File,
        _camFeatures->fourcc,
        _camFeatures->fps,
        cv::Size(_camFeatures->frame_height, _camFeatures->frame_width)
    );
}

// public static factory building VideoMaker
// -----------------------------------------
std::shared_ptr<VideoMaker> VideoMaker::VideoMakerFactory(
    std::shared_ptr<FileLocation> _fileLocation,
    std::shared_ptr<CameraFeatures> _camFeatures
)
{
    VideoMaker vm = VideoMaker(
        _fileLocation,
        _camFeatures
    );

    return std::shared_ptr<VideoMaker>(&vm);
}

// add new frame to the file
// -------------------------
int VideoMaker::addFrame(std::shared_ptr<Frame> _nextFrame)
{
    videoSink->write(*_nextFrame->data);

    return 0;
}