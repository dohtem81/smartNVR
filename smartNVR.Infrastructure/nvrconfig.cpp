// Piotr Pedziwiatr
// 02/2024

#include "nvrconfig.hpp"

// constructor takes file location pointer
// ---------------------------------------
NVRConfig::NVRConfig(std::shared_ptr<FileLocation> _fileLocation) : fileLocation(_fileLocation)
{
    // open file with json config contects
    std::ifstream f("config.json");
    nlohmann::json data;
    f >> data;

    // set where the logfiles will be written to
    logFilesPath = data["logpath"];
    logFilesPath += "smartNVR_logs_";

    // set where individual frames are saved
    saveFramePath = data["saveframepath"];

    // set camera list
    cameraList = data["videosources"];
}

std::string NVRConfig::toString() const
{
    std::stringstream ss;
    ss << "Log Files Path: " << logFilesPath;
    ss << " Save Frame Path: " << saveFramePath;
    ss << " Camera List: ";
    for (const auto& camera : cameraList)
    {
        ss << " > " << camera;
    }
    ss << std::endl;
    return ss.str();
}