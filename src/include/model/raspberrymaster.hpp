#ifndef	__RASPBERRYMASTER_HPP__
#define	__RASPBERRYMASTER_HPP__

#include "controllerlogic.hpp"

class RaspberryMaster {

    public:
        RaspberryMaster();
        ~RaspberryMaster();
        void receiveDataFromSlave();
        void changeFormatToJSON();
        void sendDataToServer();
    
    private:
        ControllerLogic *servomotors;

};

#endif