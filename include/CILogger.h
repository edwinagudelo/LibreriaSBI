#ifndef CILOGGER_H
#define CILOGGER_H

#include <string>

namespace SBI{
    
    class CILogger {
        
        public:
            CILogger() = delete;
            virtual ~CILogger() {}

            // Functions/Methods to be implemented
            virtual void LogDebug(std::string message) = 0;
            virtual void LogWarning(std::string message) = 0;
            virtual void LogInfo(std::string message) = 0;
            virtual void LogError(std::string message) = 0;

    };
}

#endif