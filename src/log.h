
#pragma once

class Log{
    public:
        enum level { error , warning , info };        

    public:

        void showLog(level logLevel , std::string message);
    };
