// Piotr Pedziwiatr
// 02/2024

#ifndef FRAME_HPP
#define FRAME_HPP

#include <opencv2/opencv.hpp>
#include <chrono>

struct Frame
{
    Frame(cv::Mat*);
private:
    Frame() : timeStamp(std::chrono::system_clock::now()) {}
    cv::Mat *data;
    std::chrono::system_clock::time_point timeStamp;
};

#endif