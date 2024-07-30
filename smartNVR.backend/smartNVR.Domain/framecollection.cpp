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
    // lock colection
    std::lock_guard<std::mutex> lock(mtx);
    
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
    // lock colection
    std::lock_guard<std::mutex> lock(mtx);

    if (frames.size() < 1)
        return nullptr;
    
    auto frameIt = frames.begin();
    std::advance(frameIt, _index);
    return *frameIt;
}

// copy constructor
// ----------------
FrameCollection::FrameCollection(const FrameCollection& other)
{
    // Copy the bufferSize
    bufferSize = other.bufferSize;

    // Copy the frames
    for (const auto& frame : other.frames)
    {
        frames.push_back(std::make_shared<Frame>(*frame));
    }
}


// assignment operator
// -------------------
FrameCollection& FrameCollection::operator=(const FrameCollection& other)
{
    // lock current collection
    std::lock_guard<std::mutex> lock(mtx);
    
    if (this != &other)
    {
        // Copy the bufferSize
        bufferSize = other.bufferSize;

        // Copy the frames
        frames.clear();
        for (const auto& frame : other.frames)
        {
            frames.push_back(std::make_shared<Frame>(*frame));
        }
    }
    return *this;
}

// clear collection
// ----------------
void FrameCollection::clear()
{
    // lock current collection
    std::lock_guard<std::mutex> lock(mtx);
    
    while(!frames.empty())
    {
        std::shared_ptr<Frame> ftbd = frames.front();
        frames.pop_front();
        ftbd->release();
    }
}