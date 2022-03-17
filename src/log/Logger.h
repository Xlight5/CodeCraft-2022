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

/**
 * @brief 日志类型
 */
enum LogMode
{
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
    
    void SetMode(LogMode logMode, std::string logFile = "")
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
    LogMode           _logMode;
    std::ofstream     _logFile;
};

#define LOG Logger::Instance()<<"\n"<<GetTimeStr()