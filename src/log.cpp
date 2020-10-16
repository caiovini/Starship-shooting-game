#include<iostream>

#include "log.h"

void Log::showLog(level logLevel , std::string message){


    switch (logLevel){
        case error:
            std::cout << std::string("error: ").append(message) << std::endl;
            break;
            
        case warning:
            std::cout << std::string("warning: ").append(message) << std::endl;
            break;

        case info:
            std::cout << std::string("info: ").append(message) << std::endl;
            break;
    }

}