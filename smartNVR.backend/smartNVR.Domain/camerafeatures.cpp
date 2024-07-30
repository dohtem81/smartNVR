// Piotr Pedziwiatr
// 02/2024

#include "camerafeatures.hpp"


// CameraFeatures factory
// -----------------------
std::shared_ptr<CameraFeatures> CameraFeatures::CameraFeaturesFactory(std::shared_ptr<cv::VideoCapture> cap_ptr)
{
    CameraFeatures *local_cf = new CameraFeatures(
        cap_ptr->get(cv::CAP_PROP_FPS),
        cap_ptr->get(cv::CAP_PROP_FRAME_WIDTH),
        cap_ptr->get(cv::CAP_PROP_FRAME_HEIGHT),
        cap_ptr->getBackendName(),
        cv::VideoWriter::fourcc('X', 'V', 'I', 'D') //static_cast<int>(cap_ptr->get(cv::CAP_PROP_FOURCC))
    );

    // convert raw pointer to chared one
    std::shared_ptr<CameraFeatures> cf(local_cf);

    return cf;
}

// to_string method for logging
// ----------------------------
std::string CameraFeatures::to_string(std::shared_ptr<CameraFeatures> cf)
{
    return cf->to_string();
}

// to_string that is not static method
// -----------------------------------
std::string CameraFeatures::to_string()
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "FPS{" << fps << "};screen res{";
    oss << std::setprecision(0) << frame_width << "x" << frame_height << "};backend:{" << backend << "};fourcc:{" << std::to_string(fourcc) << "}";

    return oss.str();    
}