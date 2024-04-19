// Piotr Pedziwiatr
// 02/2024

#ifndef NVRMAIN_HPP
#define NVRMAIN_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include "../smartNVR.Application/camera.hpp"
#include "../smartNVR.Infrastructure/nvrconfig.hpp"
#include "../Common/filelocation.hpp"
#include "../smartNVR.Application/framesaver.hpp"
#include "../smartNVR.Application/videomaker.hpp"
#include "../Common/FileNameGenerator.hpp"
#include <map>
#include <string>
#include <map>
#include <memory>
#include <sstream>
#include <chrono>
#include <thread>

class NVRMain
{
public:
    friend std::shared_ptr<NVRMain> NVRMainFactory(std::shared_ptr<FileLocation>);
    static bool initialized;

    void run();
    pthread_t nvr_thread;

private:
    static void *nvrMainLoop(void *);
    void *mainLoop();
    //pthread_t nvr_thread;

    NVRMain(std::shared_ptr<NVRConfig>);
    std::shared_ptr<NVRConfig> nvrConfig;
    bool active;

    std::map<std::string, Camera> cameras;
    std::shared_ptr<spdlog::logger> logger;
    std::map<std::string, std::shared_ptr<VideoMaker>> videoMakers;
};

// forward definition of the freind method
std::shared_ptr<NVRMain> NVRMainFactory(std::shared_ptr<FileLocation>);

#endif // NVRMAIN_HPP