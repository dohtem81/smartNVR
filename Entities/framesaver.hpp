// Piotr Pedziwiatr
// 02/2024

#ifndef FRAMESAVER_HPP
#define FRAMESAVER_HPP

#include <string>
#include <opencv2/opencv.hpp>
#include "filelocation.hpp"
#include "frame.hpp"
#include "framecollection.hpp"
#include <filesystem>


class FrameSaver
{
public:
    static int SaveFrame(FileLocation _destination, Frame* _frame);
    static int SaveFrame(
        FileLocation _destination,
        FrameCollection _sourceCollection,
        int index);
};

#endif