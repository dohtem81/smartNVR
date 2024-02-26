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
    static CameraFeatures* CameraFeaturesFactory(cv::VideoCapture*);
    static std::string to_string(CameraFeatures*);

private:
    CameraFeatures(
        double _fps,
        double _frame_width,
        double _frame_height
    ) : fps(_fps), frame_width(_frame_width), frame_height(_frame_height) {}

   
};

#endif // CAMERAFEATURES_HPP