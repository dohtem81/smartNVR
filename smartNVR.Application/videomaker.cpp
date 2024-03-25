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
    pathAndFile = _fileLocation->getPath() + _fileLocation->getFile();

    videoSink = std::make_unique<cv::VideoWriter>(
        pathAndFile,
        _camFeatures->fourcc,
        _camFeatures->fps,
        cv::Size(_camFeatures->frame_width, _camFeatures->frame_height)
    );
}

// public static factory building VideoMaker
// -----------------------------------------
std::shared_ptr<VideoMaker> VideoMaker::VideoMakerFactory(
    std::shared_ptr<FileLocation> _fileLocation,
    std::shared_ptr<CameraFeatures> _camFeatures,
    std::shared_ptr<FrameCollection> _frameCollection
)
{
    VideoMaker *vm = new VideoMaker(
        _fileLocation,
        _camFeatures
    );

    if (_frameCollection) {
        vm->CreateVideo(*_frameCollection);
    } else {
        return std::shared_ptr<VideoMaker>(vm); 
    }

    return std::shared_ptr<VideoMaker>(vm);
}

// public static factory building VideoMaker
// -----------------------------------------
std::shared_ptr<VideoMaker> VideoMaker::VideoMakerFactory(
    std::shared_ptr<FileLocation> _fileLocation,
    std::shared_ptr<CameraFeatures> _camFeatures
)
{
    VideoMaker *vm = new VideoMaker(
        _fileLocation,
        _camFeatures
    );
    {
        return std::shared_ptr<VideoMaker>(vm); 
    }

    return std::shared_ptr<VideoMaker>(vm);
}

// add new frame to the file
// -------------------------
int VideoMaker::addFrame(std::shared_ptr<Frame> _nextFrame)
{
    if (_nextFrame->empty())
        return -2;

    if (!videoSink->isOpened())
        return -1;

    videoSink->write(*_nextFrame);
    return 0;
}

// create video from the collection of frames
// ------------------------------------------
int VideoMaker::CreateVideo(FrameCollection _frames)
{
    for (int i = 0; i < _frames.getSize(); i++)
    {
        addFrame(_frames.getFrame(i));
    }

    videoSink->release();
    return 0;
}