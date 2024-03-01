// Piotr Pedziwiatr
// 02/2024

#ifndef ICAMERA_HPP
#define ICAMERA_HPP

#include <opencv2/opencv.hpp>

class ICamera
{
public:
    virtual std::shared_ptr<Frame> returnLastFrame() = 0;
};

#endif