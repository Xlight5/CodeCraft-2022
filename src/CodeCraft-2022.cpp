#include <iostream>

#include "log/Logger.h"
#include "data/DataDefine.h"
#include "data/DataReader.h"

int main(int argc, char** argv) {
    std::string workPath = "/home/haorui/haorui/CodeCraft-2022";

    Logger::Instance().SetMode(LogMode::LOG_CONSLOE | LogMode::LOG_FILE, workPath + "/CodeCraft-2022.log");

    // 1 - config.ini
    std::shared_ptr<data::Config> config = std::make_shared<data::Config>();
    data::ConfigReader configReader(workPath + "/data/config.ini");
    configReader.Read(config);

    // 2 - demand.csv
    std::deque<data::BandwithDemand> bandwithDemand;
    data::BandwithDemandsReader       bandwithDemandsReader(workPath + "/data/demand.csv");
    bandwithDemandsReader.Read(bandwithDemand);

    // 3 - site_bandwith.csv
    std::shared_ptr<data::SiteBandwidth> siteBandwidth = std::make_shared<data::SiteBandwidth>();
    data::SiteBandwithReader siteBandwithReader(workPath + "/data/site_bandwidth.csv");
    siteBandwithReader.Read(siteBandwidth);

    // 4 - qos.csv
    std::shared_ptr<data::NetWorkDelay> netWorkDelay = std::make_shared<data::NetWorkDelay>();
    data::NetWorkDelayReader netWorkDelayReader(workPath + "/data/qos.csv");
    netWorkDelayReader.Read(netWorkDelay);

	return 0;
}
