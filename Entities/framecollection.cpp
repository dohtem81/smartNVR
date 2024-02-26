#include "framecollection.hpp"

// -------------
FrameCollection::FrameCollection(int _bufferSize = 100) : bufferSize(_bufferSize) {}

// -------------
FrameCollection::~FrameCollection()
{
    while(!frames.empty())
    {
        std::shared_ptr<Frame> ftbd = frames.front();
        frames.pop_front();
        ftbd->release();
    }
}

// -------------
int FrameCollection::addFrame(std::shared_ptr<Frame> _sourceFrame)
{
    frames.push_back(_sourceFrame);

    if (frames.size() > bufferSize)
    {
        std::shared_ptr<Frame> ftbd = frames.front();
        frames.pop_front();
        ftbd->release();
    }
    
    return frames.size();
}

// -------------
int FrameCollection::getSize()
{
    return frames.size();
}

// -------------
std::shared_ptr<Frame> FrameCollection::getFrame(int _index = 0)
{
    if (frames.size() < 1)
        return nullptr;
    
    auto frameIt = frames.begin();
    std::advance(frameIt, _index);
    return *frameIt;
}