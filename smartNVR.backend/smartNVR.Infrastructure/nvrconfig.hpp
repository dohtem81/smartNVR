// Piotr Pedziwiatr
// 02/2024

#ifndef NVRCONFIG_HPP
#define NVRCONFIG_HPP

#include <memory>
#include "../Common/FileLocation.hpp"
#include "../Common/iToString.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

struct NVRConfig : public iToString
{
public:
    NVRConfig(std::shared_ptr<FileLocation>);

    // getters
    std::shared_ptr<FileLocation> getFileLocation() { return fileLocation; }
    std::string getLogFilesPath() { return logFilesPath; }
    std::string getSaveFramePath() { return saveFramePath; }
    nlohmann::json getCameraList() { return cameraList; }

    std::string toString() const override;
private:
    std::shared_ptr<FileLocation> fileLocation;
    std::string logFilesPath;
    std::string saveFramePath;
    nlohmann::json cameraList;
    int ttl;
};

#endif // NVRCONFIG_HPP