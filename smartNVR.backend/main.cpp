#include <iostream>
#include <memory>
#include "Common/FileLocation.hpp"
#include "smartNVR.Application/nvrmain.hpp"

using namespace std;


int main()
{
    std::shared_ptr<FileLocation> configFileLocation = std::make_shared<FileLocation>("./", "config.json");
    std::shared_ptr<NVRMain> smartNvr = NVRMainFactory(configFileLocation);
    smartNvr->run();
    pthread_join(smartNvr->nvr_thread, NULL);

    cout << configFileLocation->toString() << endl;
}