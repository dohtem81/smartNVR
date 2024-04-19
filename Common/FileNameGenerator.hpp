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
        static std::string GenerateNVRChapterFileName(std::chrono::time_point<std::chrono::high_resolution_clock> *_refTime)
        {
            std::time_t now = std::time(nullptr);
            std::tm* current_time = std::localtime(&now);

            int year = current_time->tm_year + 1900;
            int month = current_time->tm_mon + 1;
            int day = current_time->tm_mday;

            // extract minutes from current time and previous time, find first digit of minutes and compare, set flag for new vide file creation
            std::chrono::minutes cMinutes = std::chrono::duration_cast<std::chrono::minutes>(_refTime->time_since_epoch());
            int currentMinutes = (cMinutes.count() % 60 / 10) * 10;         
            int currentHour = std::chrono::duration_cast<std::chrono::hours>(_refTime->time_since_epoch()).count();

            return std::to_string(year) + "_" + std::to_string(month) + "_" +  std::to_string(day)
                + std::to_string(currentHour) + std::to_string(currentMinutes) + "_video.avi";
        }
};

#endif // FILE_NAME_GENERATOR_HPP