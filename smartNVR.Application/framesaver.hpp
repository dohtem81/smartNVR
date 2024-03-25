// Piotr Pedziwiatr
// 02/2024

#ifndef FRAMESAVER_HPP
#define FRAMESAVER_HPP

#include <string>
#include <opencv2/opencv.hpp>
#include "../Common/FileLocation.hpp"
#include "../smartNVR.Domain/frame.hpp"
#include "../smartNVR.Domain/framecollection.hpp"
#include <filesystem>
#include <memory>


class FrameSaver
{
public:
    static int SaveFrame(FileLocation _destination, std::shared_ptr<Frame> _frame);
    static int SaveFrame(
        FileLocation _destination,
        std::shared_ptr<FrameCollection> _sourceCollection);
private:
    static std::string CheckExtensionExistance(std::string _path);
};

#endif