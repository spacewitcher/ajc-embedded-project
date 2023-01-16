#include "app.hpp"
#include "raspberrymaster.hpp"


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
       RaspberryMaster master;
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