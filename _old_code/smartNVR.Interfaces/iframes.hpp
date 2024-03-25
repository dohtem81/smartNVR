// Piotr Pedziwiatr
// 02/2024

#ifndef IFRAMES_HPP
#define IFRAMES_HPP

#include <opencv2/opencv.hpp>

class iFrames
{
public:
    virtual int addFrame(std::shared_ptr<Frame>) = 0; // return total number of stored frames
    virtual int getSize() = 0;
    //virtual Frame getFirstFrame();
    //virtual Frame getLastFrame();
};

#endif