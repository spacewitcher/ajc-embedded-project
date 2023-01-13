#include "app.hpp"

int main(int argc, char* argv[])
{
    app app;
    if(app.init(argc, argv))
    {
        app.run();
    }


}