// Piotr Pedziwiatr
// 02/2024

#include "camerafeatures.hpp"


// CameraFeatures factory
// -----------------------
CameraFeatures* CameraFeatures::CameraFeaturesFactory(cv::VideoCapture* cap_ptr)
{
    CameraFeatures *cf = new CameraFeatures(
        cap_ptr->get(cv::CAP_PROP_FPS),
        cap_ptr->get(cv::CAP_PROP_FRAME_WIDTH),
        cap_ptr->get(cv::CAP_PROP_FRAME_HEIGHT)
    );
    return cf;
}

// to_string method for logging
// ----------------------------
std::string CameraFeatures::to_string(CameraFeatures* cf)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "FPS{" << cf->fps << "};screen res{";
    oss << std::setprecision(0) << cf->frame_width << "x" << cf->frame_height << "}";

    return oss.str();
}