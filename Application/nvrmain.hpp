// Piotr Pedziwiatr
// 02/2024

#ifndef NVRMAIN_HPP
#define NVRMAIN_HPP

#include "../Entities/camera.hpp"
#include "../Entities/nvrconfig.hpp"
#include "../Entities/filelocation.hpp"
#include "../Entities/framesaver.hpp"
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
};

// forward definition of the freind method
std::shared_ptr<NVRMain> NVRMainFactory(std::shared_ptr<FileLocation>);

#endif // NVRMAIN_HPP