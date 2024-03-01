// Piotr Pedziwiatr
// 02/2024

#ifndef CAMERAFEATURES_HPP
#define CAMERAFEATURES_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <memory>
#include <sstream>

class CameraFeatures
{
public:
    double fps;
    double frame_width;
    double frame_height;
    std::string backend;
    int fourcc;
    static std::shared_ptr<CameraFeatures> CameraFeaturesFactory(std::shared_ptr<cv::VideoCapture>);
    static std::string to_string(std::shared_ptr<CameraFeatures>);
    std::string to_string();

private:
    CameraFeatures(
        double _fps,
        double _frame_width,
        double _frame_height,
        std::string _backend,
        int _fourcc
    ) : fps(_fps), frame_width(_frame_width), frame_height(_frame_height), backend(_backend), fourcc(_fourcc) {}

   
};

#endif // CAMERAFEATURES_HPP