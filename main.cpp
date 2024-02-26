#include <iostream>
#include "Entities/camera.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <map>
#include <string>
#include <unistd.h>
#include "Application/nvrmain.hpp"

using json = nlohmann::json;
using namespace std;


int main()
{
    std::shared_ptr<FileLocation> configFileLocation = std::make_shared<FileLocation>("./", "config.json");
    std::shared_ptr<NVRMain> smartNvr = NVRMainFactory(configFileLocation);
    smartNvr->run();
    pthread_join(smartNvr->nvr_thread, NULL);
}