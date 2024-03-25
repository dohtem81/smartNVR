// Piotr Pedziwiatr
// 02/2024

#include "CameraConfiguration.hpp"

using namespace smartNVR;

std::shared_ptr<CameraConfiguration> CameraConfiguration::ConfigurationFactory(std::shared_ptr<FileLocation> _configFile)
{
    return std::make_shared<CameraConfiguration>(*(new CameraConfiguration(_configFile)));;
}
