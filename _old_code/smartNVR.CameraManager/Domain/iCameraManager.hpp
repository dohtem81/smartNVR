// Piotr Pedziwiatr
// 02/2024

#ifndef ICAMERAMANAGER_HPP
#define ICAMERAMANAGER_HPP

#include "../../Common/iConfiguration.hpp"

namespace smartNVR {

    class iCameraManager
    {
    public:
        virtual void CameraManagerFactory(void *_configPtr) const = 0;

    protected:


    private:


    };

} // namespace smartNVR

#endif // ICAMERAMANAGER_HPP