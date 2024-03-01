#include "framesaver.hpp"

// save single frame into provided desination
// ------------------------------------------
int FrameSaver::SaveFrame(FileLocation _destination, std::shared_ptr<Frame> _frame)
{
    std::string fullSavePAthAndFile = _destination.Path + "/" + _destination.File;
    cv::imwrite(fullSavePAthAndFile, *(_frame));

    return std::filesystem::file_size(fullSavePAthAndFile);
}

// save single frame into provided desination
// index specifies which frame out fo collection needs to be saved
// ------------------------------------------
int FrameSaver::SaveFrame(
        FileLocation _destination,
        FrameCollection _sourceCollection,
        int index)
{
    std::string fullSavePathAndFile = _destination.Path + "/" + _destination.File;

    // check if index is not out of bounds
    if (index >= _sourceCollection.getSize())
        return -1;

    cv::imwrite(fullSavePathAndFile, *_sourceCollection.getFrame(index));

    return std::filesystem::file_size(fullSavePathAndFile);
}