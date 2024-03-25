// Piotr Pedziwiatr
// 02/2024

#ifndef CAMERACONFIGURATION_HPP
#define CAMERACONFIGURATION_HPP

#include "../../Common/iConfiguration.hpp"
#include <memory>

namespace smartNVR
{
    class CameraConfiguration : public Common::iConfiguration
    {
    public:
        static std::shared_ptr<CameraConfiguration> ConfigurationFactory(std::shared_ptr<FileLocation> _configFile);
        
        // std::shared_ptr<iConfiguration> getConfig() const {
        //     return std::make_shared<CameraConfiguration>(this);
        // }

    protected:
        CameraConfiguration(std::shared_ptr<FileLocation> _pathAndFileName) : iConfiguration(_pathAndFileName) {}

        std::string name;

    private:


    };
}

#endif // CAMERACONFIGURATION_HPP