#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>


namespace data
{

/**
 * @brief  配置项
 * @sa     config.ini
 */
struct Config
{
public:
    uint32_t qosConstraint = 0;   // Qos 约束，上限 400 ms
public:
    static constexpr uint32_t kQosConstraintMax = 400;
};

/**
 * @brief 网络延迟
 * @sa    qos.csv
 */
struct NetWorkDelay
{
public:
    using NetworkDelayMap = std::unordered_map<std::string /* 客户节点 ID */, std::unordered_map<std::string /* 边缘节点 */, uint32_t /* 延迟(ms) */>>;
public:
    /**
     * @brief      获取网络延迟
     * @param[in]  clientNode : 客户节点
     * @param[in]  siteNode : 边缘节点
     * @return     延迟(ms)
     */
    uint32_t GetNetWorkDelay(const std::string& clientNode, const std::string& siteNode)
    {
        return _networkDelayMap[clientNode][siteNode];
    }
public:
    friend class NetWorkDelayReader;
private:
    NetworkDelayMap _networkDelayMap;
};

/**
 * @brief  边缘节点带宽
 * @sa     site_bandwith.csv
 */
struct SiteBandwidth
{
public:
    using SiteBandwithMap = std::unordered_map<std::string /* 边缘节点 */, uint32_t /* 带宽 */>;
public:
    /**
     * @brief      获取带宽
     * @param[in]  siteNode : 边缘节点
     * @return     带宽 (MB)
     */
    uint32_t GetBandwith(const std::string& siteNode)
    {
        return _siteBandwidthMap[siteNode];
    }
public:
    friend class SiteBandwithReader;
private:
    SiteBandwithMap _siteBandwidthMap;
};

/**
 * @brief 一个时刻的带宽需求
 * @sa    demand.csv
 */
struct BandwithDemand
{
public:
    using ClientBandwithDemand = std::unordered_map<std::string /* 客户节点 */, uint32_t /* 需求带宽 */>;
public:
    /**
     * @brief      获取客户节点的需求带宽
     * @param[in]  clientNode : 客户节点
     * @return     需求带宽 (MB)
     */
    uint32_t GetClientBandwithDemand(const std::string& clientNode)
    {
        return _clientBandwithDemand[clientNode];
    }

public:
    std::string           _mtime;  // 时间
    ClientBandwithDemand  _clientBandwithDemand;
};

} // namespace data