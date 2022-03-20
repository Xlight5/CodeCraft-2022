#pragma once
#include <memory>
#include <string>
#include <vector>
#include <deque>

#include "DataDefine.h"

namespace data
{

namespace field
{
constexpr char kEqual = '=';
constexpr char kComma = ',';
} // namespace field

/**
 * @brief config.ini 读取器
 */
class ConfigReader
{
public:
    explicit ConfigReader(const std::string& filePath):_filePath(filePath){};
    void Read(std::shared_ptr<Config> config);
private:
    std::string kConfig = "[config]";
    std::string kQosConstraint = "qos_constraint";
public:
    std::string _filePath;
};

/**
 * @brief qos.csv 读取器
 */
class NetWorkDelayReader
{
public:
    explicit NetWorkDelayReader(const std::string& filePath):_filePath(filePath){};
    void Read(std::shared_ptr<NetWorkDelay> netWorkDelay);
public:
    std::string kSiteName = "site_name";
public:
    std::string _filePath;
};


/**
 * @brief  site_bandwith.csv 读取器
 */
class SiteBandwithReader
{
public:
    explicit SiteBandwithReader(const std::string& filePath):_filePath(filePath){};
    void Read(std::shared_ptr<SiteBandwidth> siteBandwith);

public:
    std::string kSiteName = "site_name";
    std::string kBandWidth = "bandwidth";

public:
    std::string _filePath;
};

/**
 * @brief demand.csv 读取器
 */
class BandwithDemandsReader
{
public:
    explicit BandwithDemandsReader(const std::string& filePath):_filePath(filePath){};
    void Read(std::deque<BandwithDemand>& bandwithDemands);
public:
    std::string kMtime = "mtime";
public:
    std::string _filePath;
};

} // namespace data