// Piotr Pedziwiatr
// 02/2024

#ifndef FRAMECOLLECTION_HPP
#define FRAMECOLLECTION_HPP

#include <queue>
#include "frame.hpp"
#include "iframes.hpp"

class FrameCollection : public iFrames
{
public:
    FrameCollection();
    //FrameCollection(FrameCollection*, int, int);
    // from interface iFrames
    int addFrame(Frame*);
    int getSize();

private:
    std::queue<Frame> frames;
    //Camera* source;

};

#endif