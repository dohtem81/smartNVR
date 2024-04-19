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

    std::map<std::string, Camera>::iterator currentCamera = cameras.end();

    while(active)
    {
            previousTime = currentTime;
            currentTime = std::chrono::high_resolution_clock::now();

            // extract minutes from current time and previous time, find first digit of minutes and compare, set flag for new vide file creation
            std::chrono::minutes currentMinutes = std::chrono::duration_cast<std::chrono::minutes>(currentTime.time_since_epoch());
            std::chrono::minutes previousMinutes = std::chrono::duration_cast<std::chrono::minutes>(previousTime.time_since_epoch());
            int currentMinutesFirstDigit = currentMinutes.count() % 60 / 10;
            int previousMinutesFirstDigit = previousMinutes.count() % 60 / 10;

            std::chrono::milliseconds timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - aliveMsgTime);

        // save pending frames from each camera
        for (auto& camera : cameras)
        {
            if (camera.second.isConected() && camera.second.IsStreaming())
            {
                // add video maker for this camera if not done already
                if (videoMakers.find(camera.first) == videoMakers.end() || currentMinutesFirstDigit != previousMinutesFirstDigit)
                {
                    // check if videomaker contains already camera.first key, if it does, remove it
                    if (videoMakers.find(camera.first) != videoMakers.end())
                    {
                        videoMakers.erase(camera.first);
                        spdlog::info("video maker for " + camera.first + " removed");
                    }
                    
                    std::shared_ptr<VideoMaker> vm = VideoMaker::VideoMakerFactory(
                        std::make_shared<FileLocation>("./videos/" + camera.first + "/", camera.first + "_" 
                            + FileNameGenerator::GenerateNVRChapterFileName(&currentTime)),
                        camera.second.GetFeatures()
                    );

                    videoMakers.insert({camera.first, vm});
                    spdlog::info("video maker for " + camera.first + " added");
                } 
                else 
                {
                    if (camera.second.GetFrameCollection()->getSize() > 0)
                    {
                        std::shared_ptr<FrameCollection> fc = camera.second.GetFrameCollection();
                        videoMakers[camera.first]->addFrames(fc);
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - creationTime);
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
    
    NVRMain::initialized = true;
}


void NVRMain::run()
{
    pthread_create(&nvr_thread, NULL, NVRMain::nvrMainLoop, this);  

    return;
}