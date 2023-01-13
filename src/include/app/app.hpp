#pragma once
#include "common.hpp"
#include "log.hpp"

class app
{
    public:
        app(){}
        ~app(){this->clean();}
        bool init(int argc, char* argv[]);
        void run();
    private:
        void clean();
        void exit();
};