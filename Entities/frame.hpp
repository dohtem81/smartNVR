// Piotr Pedziwiatr
// 02/2024

#ifndef FRAME_HPP
#define FRAME_HPP

#include <opencv2/opencv.hpp>
#include <chrono>

struct Frame : public cv::Mat
{
public:
    std::chrono::system_clock::time_point getCreationTimestamp();
private:
    std::chrono::system_clock::time_point timeStamp = std::chrono::system_clock::now();
};

#endif