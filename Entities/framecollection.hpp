// Piotr Pedziwiatr
// 02/2024

#ifndef FRAMECOLLECTION_HPP
#define FRAMECOLLECTION_HPP

#include <list>
#include "frame.hpp"
#include "iframes.hpp"
#include <memory>
#include <iterator>

class FrameCollection : public iFrames
{
public:
    FrameCollection() {}
    FrameCollection(int);
    ~FrameCollection();
    
    // from interface iFrames
    int addFrame(std::shared_ptr<Frame>);
    std::shared_ptr<Frame> getFrame(int);
    int getSize();

private:
    std::list<std::shared_ptr<Frame>> frames;
    int bufferSize;
    //Camera* source;

};

#endif