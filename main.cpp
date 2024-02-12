#include <iostream>
#include "Domains/camera.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <map>
#include <string>
#include <unistd.h>

using json = nlohmann::json;
using namespace std;

int main()
{
    // get configuration
    std::ifstream f("config.json");
    json data = json::parse(f);

    std::string logfileWPath = data["logpath"];
    logfileWPath += "smartNVR_logs_";
    std::shared_ptr<spdlog::logger> logger = spdlog::daily_logger_mt("daily_logger", logfileWPath, 0, 00);

    spdlog::info("smartNVR starting up");
    
    map<string, Camera> cameras;
    spdlog::info("building camear objects...");
    for (auto& configObject : data["videosources"])
    {
        cameras.insert({configObject["name"], Camera(configObject)});
    }
    spdlog::info("building camear objects [DONE]");

    spdlog::info("staring camera threads");
    for (auto& camera : cameras)
    {
        camera.second.activate();
    }
    spdlog::info("staring camera threads [DONE]");
    
    // wait for 5sec before shutting down cameras
    sleep(5);
    spdlog::info("shutting down cameras");
    for (auto& camera : cameras)
    {
        camera.second.deactivate();
    }
    spdlog::info("shutting down cameras [DONE]");    
}