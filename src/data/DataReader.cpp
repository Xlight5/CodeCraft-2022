#include "DataReader.h"

#include <fstream>

#include "log/Logger.h"

static std::string getLine(std::ifstream& ifs)
{
    std::string buf;
    std::getline(ifs, buf);
    if (!buf.empty() && buf.back() == '\r')
    {
        buf.pop_back();
    }
    return buf;
}

static std::deque<std::string> split(const std::string& str, char delim)
{
    std::deque<std::string> res;
    std::string tmp;
    for(const auto& elm : str)
    {
        if (delim == elm)
        {
            if(!tmp.empty())
            {
                res.push_back(tmp);
            }
            tmp.clear();
            continue;
        }
        tmp.push_back(elm);
    }
    if(!tmp.empty())
    {
        res.push_back(tmp);
    }
    return res;
}

namespace data
{

void ConfigReader::Read(std::shared_ptr<Config> config)
{
    std::ifstream ifs;
    std::string buf;
    ifs.open(_filePath);
    if(!ifs.is_open())
    {
        LOG_WARN << "open file fail , file is : " << _filePath;
        return;
    }
    buf = getLine(ifs);
    if (buf == kConfig)
    {
        LOG_INFO << "find " << kConfig;
    }
    else
    {
        LOG_WARN << "can not find " << kConfig << ", buf is: " << buf;
    }
    buf = getLine(ifs);
    if (buf.find(kQosConstraint) != std::string::npos)
    {
        LOG_INFO << "find " << kQosConstraint;
    }
    else
    {
        LOG_WARN << "can not find " << kQosConstraint << ", buf is: " << buf;
    }
    uint32_t strStart = buf.find(kQosConstraint) + kQosConstraint.size() + 1;
    buf = buf.substr(strStart, buf.size() - strStart);
    config->qosConstraint = atoi(buf.c_str());
    LOG_INFO << "qosConstraint is: " << config->qosConstraint;
}

void NetWorkDelayReader::Read(std::shared_ptr<NetWorkDelay> netWorkDelay)
{
    auto& networkDelayMap = netWorkDelay->_networkDelayMap;
    std::ifstream ifs;
    std::string buf;
    std::deque<std::string> siteNodes;
    std::deque<std::string> bufs;
    ifs.open(_filePath);
    if(!ifs.is_open())
    {
        LOG_WARN << "open file fail , file is : " << _filePath;
        return;
    }
    buf = getLine(ifs);
    siteNodes = split(buf, field::kComma);
    if (!siteNodes.empty() && siteNodes.front() == kSiteName)
    {
        LOG_INFO << "find " << kSiteName;
        siteNodes.pop_front();
    }
    else
    {
        LOG_WARN << "can not find " << kSiteName;
        return;
    }

    while(1)
    {
        if(ifs.eof())
        {
            break;
        }
        buf = getLine(ifs);
        if(buf.empty())
        {
            break;
        }
        bufs = split(buf, field::kComma);
        if (bufs.size() != siteNodes.size()+1)
        {
            LOG_WARN << "siteNodes size is: " << siteNodes.size() << ", but bufs size is: " << bufs.size();
        }
        std::string clientName = bufs.front();
        bufs.pop_front();
        size_t loopTime = bufs.size();
        std::unordered_map<std::string, uint32_t> tmp;
        for(size_t i=0; i<loopTime; i++)
        {
            tmp[siteNodes[i]] = atoi(bufs[i].c_str());
        }
        networkDelayMap[clientName] = std::move(tmp);
    }
    return;
}

void SiteBandwithReader::Read(std::shared_ptr<SiteBandwidth> siteBandwith)
{
    auto& siteBandwidthMap = siteBandwith->_siteBandwidthMap;
    std::ifstream ifs;
    std::string buf;
    std::deque<std::string> bufs;

    ifs.open(_filePath);
    if(!ifs.is_open())
    {
        LOG_WARN << "open file fail , file is : " << _filePath;
        return;
    }

    buf = getLine(ifs);
    bufs = split(buf, field::kComma);
    if (bufs.size() != 2 && bufs[0] != kSiteName && bufs[1] != kBandWidth )
    {
        LOG_WARN << "cant not find " << kSiteName << " or " << kBandWidth << ", buf is " << buf;
    }
    else
    {
        LOG_INFO << "find both " << kSiteName << " and " << kBandWidth;
    }
    while(1)
    {
        if(ifs.eof())
        {
            break;
        }
        buf = getLine(ifs);
        if(buf.empty())
        {
            break;
        }
        bufs = split(buf, field::kComma);
        if (bufs.size() != 2)
        {
            LOG_WARN << "bufs size is: " << bufs.size() << ", but it should contanin 2 element";
        }
        
        std::string siteName = bufs[0];
        uint32_t    bandwidth = atoi(bufs[1].c_str());
        siteBandwidthMap[siteName] = bandwidth;
    }
    return;
}

void BandwithDemandsReader::Read(std::deque<BandwithDemand>& bandwithDemands)
{
    std::ifstream ifs;
    std::string buf;
    std::deque<std::string> clientNodes;
    std::deque<std::string> bufs;
    ifs.open(_filePath);
    if(!ifs.is_open())
    {
        LOG_WARN << "open file fail , file is : " << _filePath;
        return;
    }
    buf = getLine(ifs);
    clientNodes = split(buf, field::kComma);
    if (!clientNodes.empty() && clientNodes.front() == kMtime)
    {
        LOG_INFO << "find " << kMtime;
        clientNodes.pop_front();
    }
    else
    {
        LOG_WARN << "can not find " << kMtime;
        return;
    }
    while(1)
    {
        if(ifs.eof())
        {
            break;
        }
        buf = getLine(ifs);
        if(buf.empty())
        {
            break;
        }
        bufs = split(buf, field::kComma);
        if(bufs.size() != clientNodes.size() + 1)
        {
            LOG_WARN << "clientNodes size is: " << clientNodes.size() << ", buf bufs size is: " << bufs.size()
                     << ", impossible condition";
            return;
        }
        BandwithDemand bandwithDemand;
        bandwithDemand._mtime = bufs.front();
        bufs.pop_front();
        size_t loopTime = bufs.size();
        for(size_t i = 0; i < loopTime; i++)
        {
            bandwithDemand._clientBandwithDemand[clientNodes[i]] = atoi(bufs[i].c_str());
        }
        bandwithDemands.push_back(bandwithDemand);
    }
    LOG_INFO << "bandwithDemands size is: " << bandwithDemands.size();
}


} // namespace data