#include "app.hpp"
#include "pipca9685.h"
#include "slaveUART.h"
#include "masterUART.h"


bool app::init(int argc, char* argv[])
{
    try
    {
        init_logs(argc >1 ? string(argv[1]): string(""));
        PLOGI << "Initialisation du programme";
        return true;
    }
    catch(const std::exception& e)
    {
        PLOGF << "Erreur à l'initialisation:" << e.what();
        return false;
    }
    
    
}

void app::run()
{
    PLOGI << "Lancement du programme";
    try
    {
       //PiPCA9685 servoController(1, 0x70);
       //servoController.initialize();
       //servoController.move(1, 180);
       //servoController.move(2, 180);
        
        enableMasterUART();
    
       
    }
    catch(const exception& e)
    {
        PLOGF << "Erreur d'exécution le programme va fermer: " << e.what();
    }
    
    this->exit();
}

void app::clean()
{
    PLOGD << "Clean du programme";
}

void app::exit()
{
    PLOGW << "Sortie  du programme";
}