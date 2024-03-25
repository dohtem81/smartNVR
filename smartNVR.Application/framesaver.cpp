#include "framesaver.hpp"

// save single frame into provided desination
// ------------------------------------------
int FrameSaver::SaveFrame(FileLocation _destination, std::shared_ptr<Frame> _frame)
{
    std::string fullSavePAthAndFile = _destination.getPath() + "/" + _destination.getFile();

    // Check if the file extension is ".jpg" or ".bmp"
    fullSavePAthAndFile = CheckExtensionExistance(fullSavePAthAndFile);
    cv::imwrite(fullSavePAthAndFile, *(_frame));

    return std::filesystem::file_size(fullSavePAthAndFile);
}

// save single frame into provided desination
// index specifies which frame out fo collection needs to be saved
// ------------------------------------------
int FrameSaver::SaveFrame(
        FileLocation _destination,
        std::shared_ptr<FrameCollection> _sourceCollection)
{   
    int bytesWritten = 0;
    for (int i = 0; i < _sourceCollection->getSize(); i++)
    {
        std::string fullSavePathAndFile = _destination.getPath() + _destination.getFile() + std::to_string(i) + ".jpg";
        try 
        {
            cv::imwrite(fullSavePathAndFile, *(_sourceCollection->getFrame(i)));
            bytesWritten += std::filesystem::file_size(fullSavePathAndFile);
        } catch (const cv::Exception& e) {
            // Handle the exception here
            // You can log the error or take any other appropriate action
            // For example, you can skip saving the frame and continue with the next one
            continue;
        }
    }    

    return bytesWritten;
}

// check for file extension existance, and return proper file and path
// --------------------------------------------------------------------
std::string FrameSaver::CheckExtensionExistance(std::string _path)
{
    std::filesystem::path filePath(_path);
    std::string extension = filePath.extension().string();
    if (extension != ".jpg" && extension != ".bmp") 
    {
        return _path + ".jpg";
    }    

    return _path;
}