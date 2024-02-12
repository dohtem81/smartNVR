#include "framecollection.hpp"

// -------------
//FrameCollection::FrameCollection(Camera* _source) : source(_source) {}
FrameCollection::FrameCollection() {}

// // -------------
// FrameCollection::FrameCollection(FrameCollection *_source, int from, int to)
// {

// }

// -------------
int FrameCollection::addFrame(Frame * _sourceFrame)
{
    frames.push(*_sourceFrame);
    
    return frames.size();
}

// -------------
int FrameCollection::getSize()
{
    return frames.size();
}