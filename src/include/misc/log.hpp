#pragma once
#define PLOG_CAPTURE_FILE
#include <iostream>
#include <plog/Log.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/RollingFileAppender.h>
#include "config.h"

namespace plog
{
    class MyFuncMessageFormatter
    {
    public:
        static util::nstring header()
        {
            return util::nstring();
        }
        static util::nstring format(const Record& record)
        {
            auto severity = record.getSeverity();
            util::nostringstream ss;
            switch (severity)
            {
            case plog::verbose:
            case plog::debug:
            case plog::fatal:
            ss << record.getFile() << "->" << record.getFunc() << "@" << 
            record.getLine() << ": ";
                break;
            
            default:
                break;
            }

            ss << record.getMessage() << std::endl;

            return ss.str();
        }
    };
}

static plog::ColorConsoleAppender<plog::MyFuncMessageFormatter> consoleAppender;
static plog::RollingFileAppender<plog::TxtFormatter> fileAppender("app.log", 1024*1024*1, 5);
using namespace std;
extern void init_logs(string filter);

