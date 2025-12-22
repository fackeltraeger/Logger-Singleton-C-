#include <iostream>
#include <fstream>


// added enum class for the select of loglevel like information, debug and error etc.
enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger {
private:
    std::ofstream logFile;


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

    void log_filepoener(){
        logFile.open("app.log", std::ios::app);
    }

    void log_fileCloser() {
        if (logFile.is_open())
            logFile.close();
    }

    void log(LogLevel level, const std::string& message) {
        std::string logMessage ="[" +levelToString(level) + "] " + message; //printing this on the debug terminal can be commented if needed can be enabled.
        std::cout << logMessage << std::endl;
        if (logFile.is_open())
            logFile << logMessage << std::endl;
    }
};

int main() 
{
    Logger logObj1;
    logObj1.log_filepoener(); // added function to open the logger file

    logObj1.log(LogLevel::INFO, "Program started");
    logObj1.log(LogLevel::DEBUG, "Loading config");
    logObj1.log(LogLevel::WARNING, "Low memory");
    logObj1.log(LogLevel::ERROR, "Something failed");

    logObj1.log_fileCloser(); // added function to close the logger file.

    return 0;
}


