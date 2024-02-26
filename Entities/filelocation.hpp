// Piotr Pedziwiatr
// 02/2024

#ifndef FILELOCATION_HPP
#define FILELOCATION_HPP

#include <string>

class FileLocation
{
public:
    FileLocation(
        std::string _path,
        std::string _file) : Path(_path), File(_file) {}
    std::string Path;
    std::string File;
};

#endif // FILELOCATION_HPP