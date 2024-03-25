// Piotr Pedziwiatr
// 02/2024

#ifndef CAMERAMANAGER_HPP
#define CAMERAMANAGER_HPP

#include "../Domain/iCameraManager.hpp"
#include "../../Common/FileLocation.hpp"

namespace smartNVR {

    class CameraManager : public iCameraManager
    {
    public:
        void CameraManagerFactory(void *_configPtr);

    protected:


    private:


    };

} // namespace smartNVR

#endif // ICAMERAMANAGER_HPP