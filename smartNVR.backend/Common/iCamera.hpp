#ifndef ICAMERA_HPP
#define ICAMERA_HPP

// Include any necessary headers here
#include "../Common/FileLocation.hpp"
#include <memory>

// Declare the iCamera class
class iCamera {
public:
    virtual std::shared_ptr<Frame> GetLastFrame() const = 0;
    virtual std::shared_ptr<FrameCollection> GetFrameCollection() const = 0;
    virtual bool IsStreaming() const = 0;

private:
    // Declare private member variables here

    // Declare private member functions here
};

#endif // ICAMERA_HPP