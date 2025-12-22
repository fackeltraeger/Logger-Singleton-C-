#include <iostream>
#include <fstream>
#include <ctime>
#include <mutex>

#pragma warning(disable : 4996) // disabling the compiler error. need to ommit this analyze later.


// added enum class for the select of loglevel like information, debug and error etc.
enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

std::mutex mtx;

class Logger {
private:
    std::ofstream logFile;
    bool fileOpened = false;

    std::string timeStampForLog()
    {
        std::time_t now = std::time(NULL);
        char buf[32];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now)); // uisng predefined function for the loggeing current-time in the log.
        return buf;
    }

    std::string levelToString(LogLevel level) {
        switch (level) {
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::DEBUG:
            return "DEBUG";
        }
        return "LOG-ERROR";
    }

public:

    Logger(){
        logFile.open("InnformationLogger.log", std::ios::app);
        if (logFile.is_open())
            fileOpened = true;
        else
            std::cout << ":logfile open error occured.";
    }

    ~Logger() {
        if (true == fileOpened)
            logFile.close();
    }

    void log(LogLevel level, const std::string& message) {
        std::unique_lock<std::mutex> lock(mtx); // added this when using multi-threading so can escape form thr race condition.
        std::string logMessage = "[" + timeStampForLog() + "] : " +  "[" + levelToString(level) + "] : " + message + "."; // calling time function to log the current time in the log file.
        if (true == fileOpened)
            logFile << logMessage << std::endl;
    }
};

int main() 
{
    Logger logObj1;
    logObj1.log(LogLevel::INFO, "Program started");
    logObj1.log(LogLevel::DEBUG, "Loading config");
    logObj1.log(LogLevel::WARNING, "Low memory");
    logObj1.log(LogLevel::ERROR, "Something failed");

    return 0;
}


