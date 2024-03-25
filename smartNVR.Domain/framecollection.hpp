// Piotr Pedziwiatr
// 02/2024

#ifndef FRAMECOLLECTION_HPP
#define FRAMECOLLECTION_HPP

#include <list>
#include "frame.hpp"
#include <memory>
#include <iterator>
#include <mutex>

class FrameCollection
{
public:
    FrameCollection() {}
    FrameCollection(int);
    ~FrameCollection();
    
    // from interface iFrames
    int addFrame(std::shared_ptr<Frame>);
    std::shared_ptr<Frame> getFrame(int);
    int getSize();
    
    std::mutex mtx;
    
    FrameCollection(const FrameCollection&);
    FrameCollection& operator=(const FrameCollection&);

private:
    std::list<std::shared_ptr<Frame>> frames;
    int bufferSize;
};

#endif