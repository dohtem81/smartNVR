// Piotr Pedziwiatr
// 02/2024

#ifndef ICAPTUREFEATURES_HPP
#define ICAPTUREFEATURES_HPP

#include "framecollection.hpp"
#include <opencv2/opencv.hpp>

class ICaptureFeatures
{
public:
    virtual double getFPS() = 0;
    virtual double getFrameWidth() = 0;
    virtual double getFrameHeight() = 0;
};

#endif // ICAPTUREFEATURES_HPP