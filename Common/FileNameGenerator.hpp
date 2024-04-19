// Piotr Pedziwiatr
// 02/2024

#ifndef FILE_NAME_GENERATOR_HPP
#define FILE_NAME_GENERATOR_HPP

#include <chrono>
#include <string>
#include <ctime>

class FileNameGenerator
{
    public:
        static std::string GenerateNVRChapterFileName(std::time_t _refTime)
        {
            std::tm* current_time = std::localtime(&_refTime);

            int year = current_time->tm_year + 1900;
            int month = current_time->tm_mon + 1;
            int day = current_time->tm_mday;
            int hour = current_time->tm_hour;
            int minutes = (current_time->tm_min / 10) * 10;

            return std::to_string(year) + "_" + (month > 9 ? "" : "0") + std::to_string(month) + "_" +  (day > 9 ? "" : "0") + std::to_string(day)
                + (hour > 9 ? "" : "0") + std::to_string(hour) + std::to_string(minutes) + "_video.avi";
        }
};

#endif // FILE_NAME_GENERATOR_HPP