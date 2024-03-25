// Piotr Pedziwiatr
// 02/2024

#include "frame.hpp"

std::chrono::system_clock::time_point Frame::getCreationTimestamp()
{
    return this->timeStamp;
}


Frame::~Frame()
{
    this->release();
}