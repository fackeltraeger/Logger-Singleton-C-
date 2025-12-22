#include "Logger.h"

int main() 
{
    Logger logObj1;
    logObj1.log(LogLevel::INFO, "Program started");
    logObj1.log(LogLevel::DEBUG, "Loading config");
    logObj1.log(LogLevel::WARNING, "Low memory");
    logObj1.log(LogLevel::ERROR, "Something failed");

    return 0;
}


