// Piotr Pedziwiatr
// 02/2024

#include "nvrmain.hpp"

bool NVRMain::initialized = false;

// main loop heklper to bypass limitation of thread based on non-static class method
// ---------------------------------------------------------------------------------
void *NVRMain::nvrMainLoop(void *context)
{
    return static_cast<NVRMain*>(context)->mainLoop();
}

// main loop controlling NVR
void *NVRMain::mainLoop()
{
    spdlog::info("smartNVR is active and running");
    int sleepCounter = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::high_resolution_clock> previousTime = currentTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> aliveMsgTime = currentTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> creationTime = currentTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> saveTime = currentTime;

    while(active)
    {
        previousTime = currentTime;
        currentTime = std::chrono::high_resolution_clock::now();

        std::chrono::milliseconds timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - aliveMsgTime);
        if (timeDiff.count() > 5000)
        {
            // log heartbeat
            spdlog::info("smartNVR alive");

            aliveMsgTime = currentTime;
        }

        // timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - saveTime);
        // if (timeDiff.count() > 1000)
        // {
        //     for (auto& camera : cameras)
        //     {
        //         camera.second.saveCurrentFrame();
        //     }

        //     saveTime = currentTime;
        // }        

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - creationTime);
        //active = timeDiff.count() < 20000;
    }

    spdlog::info("smartNVR will shut down");
    return 0;
}

// factory constructing NVRMain
// ----------------------------
std::shared_ptr<NVRMain> NVRMainFactory(std::shared_ptr<FileLocation> configFileLocation)
{
    if (NVRMain::initialized)
        return nullptr;
    
    std::shared_ptr<NVRConfig> nvrConfig = std::make_shared<NVRConfig>(configFileLocation);
    NVRMain* _nvrmain = new NVRMain(nvrConfig);

    std::shared_ptr<NVRMain> nvrMianUPtr(_nvrmain);
    return nvrMianUPtr;
}

// private contructor to build NVRMain class
// -----------------------------------------
NVRMain::NVRMain(std::shared_ptr<NVRConfig> _nvrConfig) :
    active(true)
{
    // setup logger
    logger = spdlog::daily_logger_mt("daily_logger", _nvrConfig->getLogFilesPath(), 0, 00);

    // welcome message
    spdlog::info("smartNVR says hello!");

    // setup cameras
    spdlog::info("build camera camera objects from config");
    for (auto& configObject : _nvrConfig->getCameraList())
    {
        std::ostringstream oss;
        oss << "adding " << configObject["name"];
        spdlog::info(oss.str());
        cameras.insert({configObject["name"], Camera(configObject)});
    }    

    spdlog::info("staring camera threads");
    for (auto& camera : cameras)
    {    
        camera.second.activate();
    }
    spdlog::info("staring camera threads [DONE]");  

    //std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    //pthread_create(&nvr_thread, NULL, NVRMain::nvrMainLoop, this);  
    
    NVRMain::initialized = true;
}


void NVRMain::run()
{
    pthread_create(&nvr_thread, NULL, NVRMain::nvrMainLoop, this);  

    return;
}