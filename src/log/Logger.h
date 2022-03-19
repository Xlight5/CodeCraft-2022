#pragma once
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

static std::string GetTimeStr()
{
    constexpr uint32_t kBufSize = 256;
    static char buf[kBufSize];
    time_t t = time(NULL);
    tm* tm = NULL;
    tm = localtime(&t);
    if(tm)
    {
        strftime(buf, kBufSize, "%Y-%m-%d %H:%M:%S", tm);
        return std::string() + " [" + buf + "] ";
    }
    else
    {
        return "[]";
    }
}

static std::string GetFileName(const std::string& fileName)
{
    std::string res = fileName;
    size_t pos = fileName.rfind('/');
    if (pos != std::string::npos)
    {
        pos += 1;
        res = res.substr(pos, res.size()-pos);
    }
    return res;
}

/**
 * @brief 日志类型
 */
enum LogMode
{
    LOG_NONE    = 0x00,    // 无
    LOG_CONSLOE = 0x01,    // 控制台
    LOG_FILE    = 0x02     // 文件
};

/**
 * @brief 日志器
 */
class Logger
{
public:
    /**
     * @brief 获取单例
     */
    static Logger& Instance()
    {
        static Logger _logger;
        return _logger;
    }
    
    void SetMode(uint32_t logMode, std::string logFile = "")
    {
        _logMode = logMode;
        if (IsFile() && !logFile.empty())
        {
            _logFile.open(logFile);
        }
    }

    template<typename T>
    Logger& operator<<(const T& t)
    {
        if (IsConsle())
        {
            std::cout << t;
        }
        if (IsFile())
        {
            _logFile << t;
        }
        return Instance();
    }

public:
    Logger() = default;
    ~Logger()
    {
        Instance() << "\n";
    }

private:
    bool IsConsle() const
    {
        return _logMode & LogMode::LOG_CONSLOE;
    }
    bool IsFile() const
    {
        return _logMode & LogMode::LOG_FILE;
    }
private: 
    uint32_t          _logMode = LogMode::LOG_NONE;
    std::ofstream     _logFile;
};

#define LOG                      Logger::Instance()<<"\n"<<GetTimeStr()
#define LOG_INFO                 LOG << "[INFO]"  << " [" << GetFileName(__FILE__) << ":"  << __FUNCTION__ << ":" << __LINE__ << "] "
#define LOG_WARN                 LOG << "[WARN]"  << " [" << GetFileName(__FILE__) << ":"  << __FUNCTION__ << ":" << __LINE__ << "] "
#define LOG_ERROR                LOG << "[ERROR]" << " [" << GetFileName(__FILE__) << ":" << __FUNCTION__  << ":" << __LINE__ << "] "